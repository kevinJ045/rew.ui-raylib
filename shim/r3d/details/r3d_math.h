#ifndef R3D_MATH_H
#define R3D_MATH_H

#include <raylib.h>
#include <raymath.h>
#include <string.h>

#include "./r3d_simd.h"

/* === Helper === */

#ifndef R3D_RESTRICT
#   if defined(_MSC_VER)
#       define R3D_RESTRICT __restrict
#   else
#       define R3D_RESTRICT restrict
#   endif
#endif

/* === Constants === */

#define R3D_MATRIX_IDENTITY     \
    (Matrix) {                  \
        1.0f, 0.0f, 0.0f, 0.0f, \
        0.0f, 1.0f, 0.0f, 0.0f, \
        0.0f, 0.0f, 1.0f, 0.0f, \
        0.0f, 0.0f, 0.0f, 1.0f, \
    }

/* === Functions === */

static inline bool r3d_matrix_is_identity(const Matrix* matrix)
{
    return (0 == memcmp(matrix, &R3D_MATRIX_IDENTITY, sizeof(Matrix)));
}

static inline Matrix r3d_matrix_transpose(const Matrix* matrix)
{
    Matrix result;
    float* R3D_RESTRICT R = (float*)(&result);
    const float* R3D_RESTRICT M = (float*)(matrix);

#if defined(R3D_HAS_SSE)

    __m128 row0 = _mm_loadu_ps(&M[0]);
    __m128 row1 = _mm_loadu_ps(&M[4]);
    __m128 row2 = _mm_loadu_ps(&M[8]);
    __m128 row3 = _mm_loadu_ps(&M[12]);

    _MM_TRANSPOSE4_PS(row0, row1, row2, row3);

    _mm_storeu_ps(&R[0],  row0);
    _mm_storeu_ps(&R[4],  row1);
    _mm_storeu_ps(&R[8],  row2);
    _mm_storeu_ps(&R[12], row3);

#elif defined(R3D_HAS_NEON)

    float32x4x2_t t0 = vtrnq_f32(vld1q_f32(&M[0]), vld1q_f32(&M[4]));
    float32x4x2_t t1 = vtrnq_f32(vld1q_f32(&M[8]), vld1q_f32(&M[12]));

    vst1q_f32(&R[0],  vcombine_f32(vget_low_f32(t0.val[0]), vget_low_f32(t1.val[0])));
    vst1q_f32(&R[4],  vcombine_f32(vget_low_f32(t0.val[1]), vget_low_f32(t1.val[1])));
    vst1q_f32(&R[8],  vcombine_f32(vget_high_f32(t0.val[0]), vget_high_f32(t1.val[0])));
    vst1q_f32(&R[12], vcombine_f32(vget_high_f32(t0.val[1]), vget_high_f32(t1.val[1])));

#else
    R[0]  = M[0];   R[1]  = M[4];   R[2]  = M[8];   R[3]  = M[12];
    R[4]  = M[1];   R[5]  = M[5];   R[6]  = M[9];   R[7]  = M[13];
    R[8]  = M[2];   R[9]  = M[6];   R[10] = M[10];  R[11] = M[14];
    R[12] = M[3];   R[13] = M[7];   R[14] = M[11];  R[15] = M[15];
#endif

    return result;
}

static inline Matrix r3d_matrix_multiply(const Matrix* R3D_RESTRICT left, const Matrix* R3D_RESTRICT right)
{
    Matrix result;
    float* R3D_RESTRICT R = (float*)(&result);

    // Swap left/right to load rows as contiguous SIMD vectors.
    // This lets us treat left's rows as columns for SIMD dot-products,
    // avoiding per-element broadcasts while keeping the result correct.

    const float* R3D_RESTRICT A = (float*)(right);
    const float* R3D_RESTRICT B = (float*)(left);

#if defined(R3D_HAS_FMA_AVX)

    __m128 col0 = _mm_loadu_ps(&B[0]);
    __m128 col1 = _mm_loadu_ps(&B[4]);
    __m128 col2 = _mm_loadu_ps(&B[8]);
    __m128 col3 = _mm_loadu_ps(&B[12]);

    for (int i = 0; i < 4; i++) {
        __m128 ai0 = _mm_broadcast_ss(&A[i * 4 + 0]);
        __m128 ai1 = _mm_broadcast_ss(&A[i * 4 + 1]);
        __m128 ai2 = _mm_broadcast_ss(&A[i * 4 + 2]);
        __m128 ai3 = _mm_broadcast_ss(&A[i * 4 + 3]);

        __m128 row = _mm_mul_ps(ai0, col0);
        row = _mm_fmadd_ps(ai1, col1, row);
        row = _mm_fmadd_ps(ai2, col2, row);
        row = _mm_fmadd_ps(ai3, col3, row);

        _mm_storeu_ps(&R[i * 4], row);
    }

#elif defined(R3D_HAS_AVX)

    __m128 col0 = _mm_loadu_ps(&B[0]);
    __m128 col1 = _mm_loadu_ps(&B[4]);
    __m128 col2 = _mm_loadu_ps(&B[8]);
    __m128 col3 = _mm_loadu_ps(&B[12]);

    for (int i = 0; i < 4; i++) {
        __m128 ai0 = _mm_broadcast_ss(&A[i * 4 + 0]);
        __m128 ai1 = _mm_broadcast_ss(&A[i * 4 + 1]);
        __m128 ai2 = _mm_broadcast_ss(&A[i * 4 + 2]);
        __m128 ai3 = _mm_broadcast_ss(&A[i * 4 + 3]);

        __m128 row = _mm_add_ps(
            _mm_add_ps(_mm_mul_ps(ai0, col0), _mm_mul_ps(ai1, col1)),
            _mm_add_ps(_mm_mul_ps(ai2, col2), _mm_mul_ps(ai3, col3))
        );

        _mm_storeu_ps(&R[i * 4], row);
    }

#elif defined(R3D_HAS_SSE42)

    __m128 col0 = _mm_loadu_ps(&B[0]);
    __m128 col1 = _mm_loadu_ps(&B[4]);
    __m128 col2 = _mm_loadu_ps(&B[8]);
    __m128 col3 = _mm_loadu_ps(&B[12]);

    for (int i = 0; i < 4; i++) {
        __m128 ai0 = _mm_set1_ps(A[i * 4 + 0]);
        __m128 ai1 = _mm_set1_ps(A[i * 4 + 1]);
        __m128 ai2 = _mm_set1_ps(A[i * 4 + 2]);
        __m128 ai3 = _mm_set1_ps(A[i * 4 + 3]);

        __m128 row = _mm_add_ps(
            _mm_add_ps(_mm_mul_ps(ai0, col0), _mm_mul_ps(ai1, col1)),
            _mm_add_ps(_mm_mul_ps(ai2, col2), _mm_mul_ps(ai3, col3))
        );

        _mm_storeu_ps(&R[i * 4], row);
    }

#elif defined(R3D_HAS_SSE41)

    __m128 col0 = _mm_loadu_ps(&B[0]);
    __m128 col1 = _mm_loadu_ps(&B[4]);
    __m128 col2 = _mm_loadu_ps(&B[8]);
    __m128 col3 = _mm_loadu_ps(&B[12]);

    for (int i = 0; i < 4; i++) {
        __m128 ai = _mm_loadu_ps(&A[i * 4]);

        R[i * 4 + 0] = _mm_cvtss_f32(_mm_dp_ps(ai, col0, 0xF1));
        R[i * 4 + 1] = _mm_cvtss_f32(_mm_dp_ps(ai, col1, 0xF1));
        R[i * 4 + 2] = _mm_cvtss_f32(_mm_dp_ps(ai, col2, 0xF1));
        R[i * 4 + 3] = _mm_cvtss_f32(_mm_dp_ps(ai, col3, 0xF1));
    }

#elif defined(R3D_HAS_SSE)

    __m128 col0 = _mm_loadu_ps(&B[0]);
    __m128 col1 = _mm_loadu_ps(&B[4]);
    __m128 col2 = _mm_loadu_ps(&B[8]);
    __m128 col3 = _mm_loadu_ps(&B[12]);

    for (int i = 0; i < 4; i++) {
        __m128 ai0 = _mm_set1_ps(A[i * 4 + 0]);
        __m128 ai1 = _mm_set1_ps(A[i * 4 + 1]);
        __m128 ai2 = _mm_set1_ps(A[i * 4 + 2]);
        __m128 ai3 = _mm_set1_ps(A[i * 4 + 3]);

        __m128 row = _mm_add_ps(
            _mm_add_ps(_mm_mul_ps(ai0, col0), _mm_mul_ps(ai1, col1)),
            _mm_add_ps(_mm_mul_ps(ai2, col2), _mm_mul_ps(ai3, col3))
        );

        _mm_storeu_ps(&R[i * 4], row);
    }

#elif defined(R3D_HAS_NEON_FMA)

    float32x4_t col0 = vld1q_f32(&B[0]);
    float32x4_t col1 = vld1q_f32(&B[4]);
    float32x4_t col2 = vld1q_f32(&B[8]);
    float32x4_t col3 = vld1q_f32(&B[12]);

    for (int i = 0; i < 4; i++) {
        float32x4_t ai0 = vdupq_n_f32(A[i * 4 + 0]);
        float32x4_t ai1 = vdupq_n_f32(A[i * 4 + 1]);
        float32x4_t ai2 = vdupq_n_f32(A[i * 4 + 2]);
        float32x4_t ai3 = vdupq_n_f32(A[i * 4 + 3]);

        float32x4_t row = vmulq_f32(ai0, col0);
        row = vfmaq_f32(row, ai1, col1);
        row = vfmaq_f32(row, ai2, col2);
        row = vfmaq_f32(row, ai3, col3);

        vst1q_f32(&R[i * 4], row);
    }

#elif defined(R3D_HAS_NEON)

    float32x4_t col0 = vld1q_f32(&B[0]);
    float32x4_t col1 = vld1q_f32(&B[4]);
    float32x4_t col2 = vld1q_f32(&B[8]);
    float32x4_t col3 = vld1q_f32(&B[12]);

    for (int i = 0; i < 4; i++) {
        float32x4_t ai0 = vdupq_n_f32(A[i * 4 + 0]);
        float32x4_t ai1 = vdupq_n_f32(A[i * 4 + 1]);
        float32x4_t ai2 = vdupq_n_f32(A[i * 4 + 2]);
        float32x4_t ai3 = vdupq_n_f32(A[i * 4 + 3]);

        float32x4_t row = vmulq_f32(ai0, col0);
        row = vmlaq_f32(row, ai1, col1);
        row = vmlaq_f32(row, ai2, col2);
        row = vmlaq_f32(row, ai3, col3);

        vst1q_f32(&R[i * 4], row);
    }

#else

    for (int i = 0; i < 4; i++) {
        float ai0 = A[i * 4 + 0];
        float ai1 = A[i * 4 + 1];
        float ai2 = A[i * 4 + 2];
        float ai3 = A[i * 4 + 3];

        R[i * 4 + 0] = ai0 * B[0]  + ai1 * B[4]  + ai2 * B[8]  + ai3 * B[12];
        R[i * 4 + 1] = ai0 * B[1]  + ai1 * B[5]  + ai2 * B[9]  + ai3 * B[13];
        R[i * 4 + 2] = ai0 * B[2]  + ai1 * B[6]  + ai2 * B[10] + ai3 * B[14];
        R[i * 4 + 3] = ai0 * B[3]  + ai1 * B[7]  + ai2 * B[11] + ai3 * B[15];
    }

#endif

    return result;
}

static inline void r3d_matrix_multiply_batch(
    Matrix* R3D_RESTRICT results,
    const Matrix* R3D_RESTRICT left_matrices,
    const Matrix* R3D_RESTRICT right_matrices,
    int count)
{
#if defined(R3D_HAS_FMA_AVX)

    for (int m = 0; m < count; m++) {
        const float* R3D_RESTRICT A = (float*)(&right_matrices[m]);
        const float* R3D_RESTRICT B = (float*)(&left_matrices[m]);
        float* R3D_RESTRICT R = (float*)(&results[m]);

        __m128 col0 = _mm_loadu_ps(&B[0]);
        __m128 col1 = _mm_loadu_ps(&B[4]);
        __m128 col2 = _mm_loadu_ps(&B[8]);
        __m128 col3 = _mm_loadu_ps(&B[12]);

        for (int i = 0; i < 4; i++) {
            __m128 ai0 = _mm_broadcast_ss(&A[i * 4 + 0]);
            __m128 ai1 = _mm_broadcast_ss(&A[i * 4 + 1]);
            __m128 ai2 = _mm_broadcast_ss(&A[i * 4 + 2]);
            __m128 ai3 = _mm_broadcast_ss(&A[i * 4 + 3]);

            __m128 row = _mm_mul_ps(ai0, col0);
            row = _mm_fmadd_ps(ai1, col1, row);
            row = _mm_fmadd_ps(ai2, col2, row);
            row = _mm_fmadd_ps(ai3, col3, row);

            _mm_storeu_ps(&R[i * 4], row);
        }
    }

#elif defined(R3D_HAS_AVX)

    for (int m = 0; m < count; m++) {
        const float* R3D_RESTRICT A = (float*)(&right_matrices[m]);
        const float* R3D_RESTRICT B = (float*)(&left_matrices[m]);
        float* R3D_RESTRICT R = (float*)(&results[m]);

        __m128 col0 = _mm_loadu_ps(&B[0]);
        __m128 col1 = _mm_loadu_ps(&B[4]);
        __m128 col2 = _mm_loadu_ps(&B[8]);
        __m128 col3 = _mm_loadu_ps(&B[12]);

        for (int i = 0; i < 4; i++) {
            __m128 ai0 = _mm_broadcast_ss(&A[i * 4 + 0]);
            __m128 ai1 = _mm_broadcast_ss(&A[i * 4 + 1]);
            __m128 ai2 = _mm_broadcast_ss(&A[i * 4 + 2]);
            __m128 ai3 = _mm_broadcast_ss(&A[i * 4 + 3]);

            __m128 row = _mm_add_ps(
                _mm_add_ps(_mm_mul_ps(ai0, col0), _mm_mul_ps(ai1, col1)),
                _mm_add_ps(_mm_mul_ps(ai2, col2), _mm_mul_ps(ai3, col3))
            );

            _mm_storeu_ps(&R[i * 4], row);
        }
    }

#elif defined(R3D_HAS_SSE42) || defined(R3D_HAS_SSE)

    for (int m = 0; m < count; m++) {
        const float* R3D_RESTRICT A = (float*)(&right_matrices[m]);
        const float* R3D_RESTRICT B = (float*)(&left_matrices[m]);
        float* R3D_RESTRICT R = (float*)(&results[m]);

        __m128 col0 = _mm_loadu_ps(&B[0]);
        __m128 col1 = _mm_loadu_ps(&B[4]);
        __m128 col2 = _mm_loadu_ps(&B[8]);
        __m128 col3 = _mm_loadu_ps(&B[12]);

        for (int i = 0; i < 4; i++) {
            __m128 ai0 = _mm_set1_ps(A[i * 4 + 0]);
            __m128 ai1 = _mm_set1_ps(A[i * 4 + 1]);
            __m128 ai2 = _mm_set1_ps(A[i * 4 + 2]);
            __m128 ai3 = _mm_set1_ps(A[i * 4 + 3]);

            __m128 row = _mm_add_ps(
                _mm_add_ps(_mm_mul_ps(ai0, col0), _mm_mul_ps(ai1, col1)),
                _mm_add_ps(_mm_mul_ps(ai2, col2), _mm_mul_ps(ai3, col3))
            );

            _mm_storeu_ps(&R[i * 4], row);
        }
    }

#elif defined(R3D_HAS_NEON_FMA)

    for (int m = 0; m < count; m++) {
        const float* R3D_RESTRICT A = (float*)(&right_matrices[m]);
        const float* R3D_RESTRICT B = (float*)(&left_matrices[m]);
        float* R3D_RESTRICT R = (float*)(&results[m]);

        float32x4_t col0 = vld1q_f32(&B[0]);
        float32x4_t col1 = vld1q_f32(&B[4]);
        float32x4_t col2 = vld1q_f32(&B[8]);
        float32x4_t col3 = vld1q_f32(&B[12]);

        for (int i = 0; i < 4; i++) {
            float32x4_t ai0 = vdupq_n_f32(A[i * 4 + 0]);
            float32x4_t ai1 = vdupq_n_f32(A[i * 4 + 1]);
            float32x4_t ai2 = vdupq_n_f32(A[i * 4 + 2]);
            float32x4_t ai3 = vdupq_n_f32(A[i * 4 + 3]);

            float32x4_t row = vmulq_f32(ai0, col0);
            row = vfmaq_f32(row, ai1, col1);
            row = vfmaq_f32(row, ai2, col2);
            row = vfmaq_f32(row, ai3, col3);

            vst1q_f32(&R[i * 4], row);
        }
    }

#elif defined(R3D_HAS_NEON)

    for (int m = 0; m < count; m++) {
        const float* R3D_RESTRICT A = (float*)(&right_matrices[m]);
        const float* R3D_RESTRICT B = (float*)(&left_matrices[m]);
        float* R3D_RESTRICT R = (float*)(&results[m]);

        float32x4_t col0 = vld1q_f32(&B[0]);
        float32x4_t col1 = vld1q_f32(&B[4]);
        float32x4_t col2 = vld1q_f32(&B[8]);
        float32x4_t col3 = vld1q_f32(&B[12]);

        for (int i = 0; i < 4; i++) {
            float32x4_t ai0 = vdupq_n_f32(A[i * 4 + 0]);
            float32x4_t ai1 = vdupq_n_f32(A[i * 4 + 1]);
            float32x4_t ai2 = vdupq_n_f32(A[i * 4 + 2]);
            float32x4_t ai3 = vdupq_n_f32(A[i * 4 + 3]);

            float32x4_t row = vmulq_f32(ai0, col0);
            row = vmlaq_f32(row, ai1, col1);
            row = vmlaq_f32(row, ai2, col2);
            row = vmlaq_f32(row, ai3, col3);

            vst1q_f32(&R[i * 4], row);
        }
    }

#else

    for (int m = 0; m < count; m++) {
        const float* R3D_RESTRICT A = (float*)(&right_matrices[m]);
        const float* R3D_RESTRICT B = (float*)(&left_matrices[m]);
        float* R3D_RESTRICT R = (float*)(&results[m]);

        for (int i = 0; i < 4; i++) {
            float ai0 = A[i * 4 + 0];
            float ai1 = A[i * 4 + 1];
            float ai2 = A[i * 4 + 2];
            float ai3 = A[i * 4 + 3];

            R[i * 4 + 0] = ai0 * B[0]  + ai1 * B[4]  + ai2 * B[8]  + ai3 * B[12];
            R[i * 4 + 1] = ai0 * B[1]  + ai1 * B[5]  + ai2 * B[9]  + ai3 * B[13];
            R[i * 4 + 2] = ai0 * B[2]  + ai1 * B[6]  + ai2 * B[10] + ai3 * B[14];
            R[i * 4 + 3] = ai0 * B[3]  + ai1 * B[7]  + ai2 * B[11] + ai3 * B[15];
        }
    }

#endif
}

static inline Matrix r3d_matrix_scale_translate(const Vector3* s, const Vector3* t)
{
    return (Matrix) {
        s->x, 0.0f, 0.0f, t->x,
        0.0f, s->y, 0.0f, t->y,
        0.0f, 0.0f, s->z, t->z,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

static inline Matrix r3d_matrix_scale_rotaxis_translate(const Vector3* s, const Vector4* r, const Vector3* t)
{
    float axis_len = sqrtf(r->x * r->x + r->y * r->y + r->z * r->z);
    if (axis_len < 1e-6f) {
        return r3d_matrix_scale_translate(s, t);
    }

    float inv_len = 1.0f / axis_len;
    float x = r->x * inv_len;
    float y = r->y * inv_len; 
    float z = r->z * inv_len;
    float angle = r->w;

    float c = cosf(angle);
    float s_sin = sinf(angle);
    float one_minus_c = 1.0f - c;

    float xx = x * x, yy = y * y, zz = z * z;
    float xy = x * y, xz = x * z, yz = y * z;
    float xs = x * s_sin, ys = y * s_sin, zs = z * s_sin;

    return (Matrix) {
        s->x * (c + xx * one_minus_c),  s->x * (xy * one_minus_c - zs), s->x * (xz * one_minus_c + ys), t->x,
        s->y * (xy * one_minus_c + zs), s->y * (c + yy * one_minus_c),  s->y * (yz * one_minus_c - xs), t->y,
        s->z * (xz * one_minus_c - ys), s->z * (yz * one_minus_c + xs), s->z * (c + zz * one_minus_c),  t->z,
        0,0,0,1
    };
}

static inline Matrix r3d_matrix_scale_rotxyz_translate(const Vector3* s, const Vector3* r, const Vector3* t)
{
    float cx = cosf(r->x), sx = sinf(r->x);
    float cy = cosf(r->y), sy = sinf(r->y); 
    float cz = cosf(r->z), sz = sinf(r->z);

    float czcx = cz * cx, czsx = cz * sx;
    float szcx = sz * cx, szsx = sz * sx;

    return (Matrix) {
        s->x * (cy*cz),               s->x * (-cy*sz),             s->x * sy,      t->x,
        s->y * (sx*sy*cz + cx*sz),    s->y * (-sx*sy*sz + cx*cz),  s->y * (-sx*cy), t->y,
        s->z * (-cx*sy*cz + sx*sz),   s->z * (cx*sy*sz + sx*cz),   s->z * (cx*cy),  t->z,
        0,0,0,1
    };
}

static inline Matrix r3d_matrix_scale_rotq_translate(const Vector3* s, const Quaternion* q, const Vector3* t)
{
    float qlen = sqrtf(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);
    if (qlen < 1e-6f) {
        return r3d_matrix_scale_translate(s, t);
    }

    float inv_len = 1.0f / qlen;
    float qx = q->x * inv_len;
    float qy = q->y * inv_len;
    float qz = q->z * inv_len;
    float qw = q->w * inv_len;

    float qx2 = qx * qx, qy2 = qy * qy, qz2 = qz * qz;
    float qxqy = qx * qy, qxqz = qx * qz, qxqw = qx * qw;
    float qyqz = qy * qz, qyqw = qy * qw, qzqw = qz * qw;

    return (Matrix) {
        s->x * (1.0f - 2.0f * (qy2 + qz2)), s->x * (2.0f * (qxqy - qzqw)), s->x * (2.0f * (qxqz + qyqw)), t->x,
        s->y * (2.0f * (qxqy + qzqw)),       s->y * (1.0f - 2.0f * (qx2 + qz2)), s->y * (2.0f * (qyqz - qxqw)), t->y,
        s->z * (2.0f * (qxqz - qyqw)),       s->z * (2.0f * (qyqz + qxqw)),       s->z * (1.0f - 2.0f * (qx2 + qy2)), t->z,
        0,0,0,1
    };
}

static inline Matrix r3d_matrix_normal(const Matrix* transform)
{
    // Calculate inverse transpose (M^-1)^T directly for normal transformation
    // This is more efficient than computing inverse then transpose

    const float* m = (const float*)transform;

    float a00 = m[0], a01 = m[1], a02 = m[2], a03 = m[3];
    float a10 = m[4], a11 = m[5], a12 = m[6], a13 = m[7];
    float a20 = m[8], a21 = m[9], a22 = m[10], a23 = m[11];
    float a30 = m[12], a31 = m[13], a32 = m[14], a33 = m[15];

    float b00 = a00*a11 - a01*a10;
    float b01 = a00*a12 - a02*a10;
    float b02 = a00*a13 - a03*a10;
    float b03 = a01*a12 - a02*a11;
    float b04 = a01*a13 - a03*a11;
    float b05 = a02*a13 - a03*a12;
    float b06 = a20*a31 - a21*a30;
    float b07 = a20*a32 - a22*a30;
    float b08 = a20*a33 - a23*a30;
    float b09 = a21*a32 - a22*a31;
    float b10 = a21*a33 - a23*a31;
    float b11 = a22*a33 - a23*a32;

    float det = b00*b11 - b01*b10 + b02*b09 + b03*b08 - b04*b07 + b05*b06;
    if (fabsf(det) < 1e-6f) {
        return R3D_MATRIX_IDENTITY;
    }
    float inv_det = 1.0f / det;

    Matrix result;
    float* r = (float*)&result;

    r[0] = (a11*b11 - a12*b10 + a13*b09) * inv_det;
    r[1] = (-a10*b11 + a12*b08 - a13*b07) * inv_det;
    r[2] = (a10*b10 - a11*b08 + a13*b06) * inv_det;
    r[3] = (-a10*b09 + a11*b07 - a12*b06) * inv_det;

    r[4] = (-a01*b11 + a02*b10 - a03*b09) * inv_det;
    r[5] = (a00*b11 - a02*b08 + a03*b07) * inv_det;
    r[6] = (-a00*b10 + a01*b08 - a03*b06) * inv_det;
    r[7] = (a00*b09 - a01*b07 + a02*b06) * inv_det;

    r[8] = (a31*b05 - a32*b04 + a33*b03) * inv_det;
    r[9] = (-a30*b05 + a32*b02 - a33*b01) * inv_det;
    r[10] = (a30*b04 - a31*b02 + a33*b00) * inv_det;
    r[11] = (-a30*b03 + a31*b01 - a32*b00) * inv_det;

    r[12] = (-a21*b05 + a22*b04 - a23*b03) * inv_det;
    r[13] = (a20*b05 - a22*b02 + a23*b01) * inv_det;
    r[14] = (-a20*b04 + a21*b02 - a23*b00) * inv_det;
    r[15] = (a20*b03 - a21*b01 + a22*b00) * inv_det;

    return result;
}

#endif // R3D_MATH_H
