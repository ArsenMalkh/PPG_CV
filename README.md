# PPG_CV

Реализован **PPG(Patterned Pixel Grouping)** для фильтра Байера, 

Для ввода/ввывода использованна сторонняя библиотека [Bitmap](https://github.com/ArashPartow/bitmap).

Компиляция и запуск: (linux)
```sh
$ g++ main.cpp restorer.cpp ppg.cpp
$ ./a.out images/RGB_CFA.bmp images/Result.bmp
```

## PSNR
```sh
$ python3 metric.py image/Original.bmp image/Result.bmp
```
## Performance

Image Size = 4176x2073,  Time duration = 12.879 sec => ~0.67 megapixel/second
MSE =  85.40340687511205
PSNR =  28.816051651490483
