# This is the python code to determine the answer to the problem. It does not interact with the C++ version. The python version is mainly for testing purposes
#
#
import sys, math
import array as arr

def convert_to_base(num, base):
    representation = []
    while num > 0:
        representation.append(num % base) 
        num = int(num / base)
    return representation


# this makes sure that the current state has enough bits to be a starting seed
def fill_out(output_Stream: list, taps: list):
    if len(taps) > len(output_Stream):
        for i in range(len(taps) - len(output_Stream)):
            output_Stream.append(0)


def dot_product(array1, array2):
    product = 0
    for i in range(len(array1)):
        product += array1[i] * array2[i]
    return product

def find_req_seeds(lower_bound: int, upper_bound: int, base: int): # upper bound inclusive
    output = [1]
    for n in range(lower_bound, upper_bound + 1):
        req_Seeds = 1
        taps = convert_to_base(n, base)
        past_States = [0] * (base ** len(taps))
        past_States[0] = 1
        current_State = 0
        while 0 in past_States:
            req_Seeds += 1
            current_State = past_States.index(0)  # go to highest as of yet unrecorded state
            current_st_base2 = convert_to_base(current_State, base)
            fill_out(current_st_base2, taps)
            while past_States[current_State] == 0:  # (NOTE: THIS WILL NOT WORK FOR COMPOSITE BASES)
                past_States[current_State] = 1
                current_st_base2.insert(0, dot_product(taps, current_st_base2) % base)
                current_State = sum([current_st_base2[i] * (base ** i) for i in range(len(taps))])  # convert new state to base 10
        output.append(req_Seeds)

    return output

if __name__ == '__main__':
    #base = int(input("What is the base? >>> "))
    #nMin = max(int(input("What is the lower bound of n? >>> ")), 1) # nMin will be at least 1
    #nMax = int(input("What is the upper bound of n? >>> "))
    Output = find_req_seeds(0, 10000, 2)

    #print(f'Output is {Output}')
    
       
