# ---------- S-DES IMPLEMENTATION ----------

P10 = [3,5,2,7,4,10,1,9,8,6]
P8  = [6,3,7,4,8,5,10,9]
IP  = [2,6,3,1,4,8,5,7]
IP_INV = [4,1,3,5,7,2,8,6]
EP  = [4,1,2,3,2,3,4,1]
P4  = [2,4,3,1]

S0 = [[1,0,3,2],
      [3,2,1,0],
      [0,2,1,3],
      [3,1,3,2]]

S1 = [[0,1,2,3],
      [2,0,1,3],
      [3,0,1,0],
      [2,1,0,3]]

def permute(bits, table):
    return ''.join(bits[i-1] for i in table)

def shift_left(bits, n):
    return bits[n:] + bits[:n]

def xor(a, b):
    return ''.join('0' if i==j else '1' for i,j in zip(a,b))

def sbox_lookup(bits, box):
    row = int(bits[0] + bits[3], 2)
    col = int(bits[1] + bits[2], 2)
    return format(box[row][col], '02b')

def generate_keys(key):
    p10 = permute(key, P10)
    left, right = p10[:5], p10[5:]

    left1 = shift_left(left,1)
    right1 = shift_left(right,1)
    k1 = permute(left1 + right1, P8)

    left2 = shift_left(left1,2)
    right2 = shift_left(right1,2)
    k2 = permute(left2 + right2, P8)

    return k1, k2

def fk(bits, key):
    left, right = bits[:4], bits[4:]
    ep = permute(right, EP)
    x = xor(ep, key)
    s0 = sbox_lookup(x[:4], S0)
    s1 = sbox_lookup(x[4:], S1)
    p4 = permute(s0 + s1, P4)
    return xor(left, p4) + right

def sdes_encrypt(block, key):
    k1, k2 = generate_keys(key)
    ip = permute(block, IP)
    temp = fk(ip, k1)
    temp = temp[4:] + temp[:4]
    temp = fk(temp, k2)
    return permute(temp, IP_INV)

def sdes_decrypt(block, key):
    k1, k2 = generate_keys(key)
    ip = permute(block, IP)
    temp = fk(ip, k2)
    temp = temp[4:] + temp[:4]
    temp = fk(temp, k1)
    return permute(temp, IP_INV)





def ecb_encrypt(plaintexts, key):
    return [sdes_encrypt(p, key) for p in plaintexts]

def ecb_decrypt(ciphertexts, key):
    return [sdes_decrypt(c, key) for c in ciphertexts]





def cbc_encrypt(plaintexts, key, iv):
    ciphertexts = []
    prev = iv
    for p in plaintexts:
        x = xor(p, prev)
        c = sdes_encrypt(x, key)
        ciphertexts.append(c)
        prev = c
    return ciphertexts

def cbc_decrypt(ciphertexts, key, iv):
    plaintexts = []
    prev = iv
    for c in ciphertexts:
        p = xor(sdes_decrypt(c, key), prev)
        plaintexts.append(p)
        prev = c
    return plaintexts



def cfb_encrypt(plaintexts, key, iv):
    ciphertexts = []
    prev = iv
    for p in plaintexts:
        e = sdes_encrypt(prev, key)
        c = xor(p, e)
        ciphertexts.append(c)
        prev = c
    return ciphertexts

def cfb_decrypt(ciphertexts, key, iv):
    plaintexts = []
    prev = iv
    for c in ciphertexts:
        e = sdes_encrypt(prev, key)
        p = xor(c, e)
        plaintexts.append(p)
        prev = c
    return plaintexts




def ofb_encrypt(plaintexts, key, iv):
    ciphertexts = []
    o = iv
    for p in plaintexts:
        o = sdes_encrypt(o, key)
        ciphertexts.append(xor(p, o))
    return ciphertexts

def ofb_decrypt(ciphertexts, key, iv):
    return ofb_encrypt(ciphertexts, key, iv)


def ctr_encrypt(plaintexts, key, counter):
    ciphertexts = []
    ctr = int(counter, 2)

    for p in plaintexts:
        ctr_block = format(ctr, '08b')      # 8-bit counter
        keystream = sdes_encrypt(ctr_block, key)
        c = xor(p, keystream)
        ciphertexts.append(c)
        ctr += 1

    return ciphertexts

def ctr_decrypt(ciphertexts, key, counter):
    return ctr_encrypt(ciphertexts, key, counter)



plaintexts = ["11001010", "11001010", "11001010"]
key = "1010000010"
iv = "11110000"
counter = "00000001"

print("ECB:", ecb_encrypt(plaintexts, key))
print("CBC:", cbc_encrypt(plaintexts, key, iv))
print("CFB:", cfb_encrypt(plaintexts, key, iv))
print("OFB:", ofb_encrypt(plaintexts, key, iv))
print("CTR:", ctr_encrypt(plaintexts, key, counter))
