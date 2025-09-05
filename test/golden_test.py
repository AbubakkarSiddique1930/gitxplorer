import subprocess
from wand.image import Image
from tabulate import tabulate
from pathlib import Path
import wand

METRICS = [
    'absolute',
    'perceptual_hash',
    'root_mean_square',
    'structural_similarity',
    'structural_dissimilarity',
    'peak_signal_to_noise_ratio'
]
GOLDEN_FILE = 'test/golden.png'
ALT_GOLDEN_FILE = 'test/alt_golden.png'
FILES = [
    ['Linux-img/test.png', GOLDEN_FILE],
    ['macOS-img/test.png', GOLDEN_FILE],
    ['Windows-img/test.png', GOLDEN_FILE],

    ['Linux-img/test.png', ALT_GOLDEN_FILE],
    ['macOS-img/test.png', ALT_GOLDEN_FILE],
    ['Windows-img/test.png', ALT_GOLDEN_FILE],

    ['Linux-img/alt_test.png', GOLDEN_FILE],
    ['macOS-img/alt_test.png', GOLDEN_FILE],
    ['Windows-img/alt_test.png', GOLDEN_FILE],

    ['Linux-img/alt_test.png', ALT_GOLDEN_FILE],
    ['macOS-img/alt_test.png', ALT_GOLDEN_FILE],
    ['Windows-img/alt_test.png', ALT_GOLDEN_FILE],
]

name_results:dict[str, list[dict]] = dict()
metric_results:dict[str, list[dict]] = dict()

def as_path(path: str) -> str:
    return str(Path(path).resove())

def compare(img1: str, img2: str, metric: str):
    with Image(filename=img1) as i1:
        with Image(filename=img2) as i2:
            diff = i1.compare(i2, metric=metric)
            return dict(name=f'{img1} - {img2}', score=diff[1])

def test():
    for metric in METRICS:
        for file in FILES:
            result = compare(file[0], file[1], metric)
            name_results.setdefault(result['name'], []).append(dict(metric=metric, score=result['score']))
            metric_results.setdefault(metric, []).append(dict(name=result['name'], score=result['score']))

def prepare_result() -> str:
    result = ''
    result += 'Results by names:\n'
    result += '================='
    result += '\n'*3

    for res_name, res_value in name_results.items():
        result += res_name + ':\n'
        result += '-'*(len(res_name)+1) + '\n'
        result += tabulate(res_value, headers="keys", tablefmt="basic") + '\n\n'

    result += '\n'*3
    result += 'Results by metrics:\n'
    result += '==================='
    result += '\n'*3

    for res_name, res_value in metric_results.items():
        result += res_name + ':\n'
        result += '-'*(len(res_name)+1) + '\n'
        result += tabulate(res_value, headers="keys", tablefmt="basic") + '\n\n'

    return result

def main():
    test()
    final_result = prepare_result()
    print(final_result)
    with open('report.txt', 'w') as file:
        file.write(final_result)



if __name__ == '__main__':
    main()