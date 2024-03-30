#  Copyright 2024 Frank Vanbever
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

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
