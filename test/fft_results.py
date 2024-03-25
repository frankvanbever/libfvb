from numpy.fft import fft


def complex_testdata(num_samples):
    testdata = []
    for i in range(num_samples):
        testdata.append(i * 1.0+ i * 1.0j)

    return testdata



def complex_fft_results(num_samples):
    x = complex_testdata(num_samples)
    X = fft(x)

    for i in X:
        print(i)



if __name__ == '__main__':
    complex_fft_results(8)
