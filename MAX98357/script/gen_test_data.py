import numpy as np
from pydub import AudioSegment
import sys, os

INPUT_FILE = 'test.mp3'      # 测试音频
OUTPUT_H   = 'voice8k16b.h'
MAX_BYTES  = 64000            #数据量
SAMPLE_RATE = 8000
# ==================

def main():
    if not os.path.isfile(INPUT_FILE):
        print('file not found: %s' % INPUT_FILE)
        sys.exit(1)

    # 读文件 → 转 8 kHz → 单声道
    audio = AudioSegment.from_file(INPUT_FILE).set_frame_rate(SAMPLE_RATE).set_channels(1)

    # 转 numpy int16
    samples = np.array(audio.get_array_of_samples(), dtype=np.int16)

    # 限制长度
    max_samples = MAX_BYTES // 2
    if len(samples) > max_samples:
        samples = samples[:max_samples]

    # 调整声音大小
    vol = 0.02
    samples = (samples.astype(np.float32) * vol).astype(np.int16)

    # 写 C 数组
    with open(OUTPUT_H, 'w') as f:
        f.write('#ifndef VOICE8K16B_H\n#define VOICE8K16B_H\n\n')
        f.write(f'const int16_t voice8k16b[{len(samples)}] = {{\n')
        for i, v in enumerate(samples):
            f.write(f'{v},')
            if (i % 16) == 15: f.write('\n')
        f.write('\n};\n\n#endif\n')

if __name__ == '__main__':
    main()