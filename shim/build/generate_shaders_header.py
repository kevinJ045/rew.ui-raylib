
import sys
import os

def generate_shaders_header(shader_names, output_file):
    with open(output_file, 'w') as f:
        f.write('#ifndef SHADERS_H\n')
        f.write('#define SHADERS_H\n\n')
        f.write('// Auto-generated header that includes all shader headers\n\n')
        
        for shader_name in shader_names:
            f.write(f'#include "./shaders/{shader_name}.h"\n')
        
        f.write('\n#endif // SHADERS_H\n')

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print('Usage: python script.py <output_file> <shader_name1> [shader_name2] ...')
        sys.exit(1)
    
    output_file = sys.argv[1]
    shader_names = sys.argv[2:]
    generate_shaders_header(shader_names, output_file)
