
import sys
import os

def generate_assets_header(asset_names, output_file):
    with open(output_file, 'w') as f:
        f.write('#ifndef ASSETS_H\n')
        f.write('#define ASSETS_H\n\n')
        f.write('// Auto-generated header that includes all asset headers\n\n')
        
        for asset_name in asset_names:
            f.write(f'#include "./assets/{asset_name}.h"\n')
        
        f.write('\n#endif // ASSETS_H\n')

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print('Usage: python script.py <output_file> <asset_name1> [asset_name2] ...')
        sys.exit(1)
    
    output_file = sys.argv[1]
    asset_names = sys.argv[2:]
    generate_assets_header(asset_names, output_file)
