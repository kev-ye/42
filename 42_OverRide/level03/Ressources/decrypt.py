import sys

# python3 decrypt.py [nbr]
arg = int(sys.argv[1])

def split(s):
    return list(reversed([s[i:i + 2] for i in range(0, len(s), 2)]))

password = ''.join(split('757c7d51') + split('67667360') + split('7b66737e') + split('33617c7d'))

print('Origin:', bytes.fromhex(password).decode('utf-8'))

# decrypt with 18 as key we get: "Congratulations!"
print(f'Decrypt with {arg}:', ''.join([chr(ord(i) ^ arg) for i in bytes.fromhex(password).decode('utf-8')]))