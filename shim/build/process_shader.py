
import sys
import subprocess
import os

def process_shader(shader_file, shader_name, output_file, r3d_root):
    # Minify the shader
    result = subprocess.run([
        sys.executable, 
        os.path.join(r3d_root, 'scripts', 'glsl_minifier.py'), 
        shader_file
    ], capture_output=True, text=True)
    
    if result.returncode != 0:
        print(f'Error during minification: {result.stderr}', file=sys.stderr)
        sys.exit(1)
    
    minified_shader = result.stdout.strip()
    
    # Generate the C header
    result = subprocess.run([
        sys.executable,
        os.path.join(r3d_root, 'scripts', 'bin2c.py'),
        '--string', minified_shader,
        '--name', shader_name,
        '--type', 'char',
        output_file
    ], capture_output=True, text=True)
    
    if result.returncode != 0:
        print(f'Error during header generation: {result.stderr}', file=sys.stderr)
        sys.exit(1)

if __name__ == '__main__':
    if len(sys.argv) != 5:
        print('Usage: python script.py <shader_file> <shader_name> <output_file> <r3d_root>')
        sys.exit(1)
    
    process_shader(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])
