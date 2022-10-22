import numpy as np
from PIL import Image
import sys

def get_MSE(first: np.ndarray, second: np.ndarray) -> float:
    return np.sum((first - second) ** 2) / (first.shape[0] * first.shape[1])



def get_PSNR(first: np.ndarray, second: np.ndarray) -> float:
    mse = get_MSE(first, second)
    return 10 * np.log10(Y_MAX * Y_MAX / mse)


original_img = Image.open(str(sys.argv[1]))
recovered_img = Image.open(str(sys.argv[2]))

original = np.array(original_img)
recovered = np.array(recovered_img)

Y_MAX = 255
mse = get_MSE(original, recovered)
psnr = get_PSNR(original, recovered)

print("MSE = ", mse)
print("PSNR = ", psnr)