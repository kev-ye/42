// External Dependencies
import * as crypto from "crypto";
import * as fs from "fs";

const path = './localSecret.txt';

const algorithm = 'aes-256-cbc'; // Using AES encryption
const secretKey = fs.readFileSync(path); // local secret by crypto.randomBytes(32)
const iv = crypto.randomBytes(16);

export interface IEncryption {
  iv: string,
  encryptedData: string
}

export const encrypt = (text: string): IEncryption => {
  const cipher = crypto.createCipheriv(algorithm, secretKey, iv);
  const encrypted = Buffer.concat([cipher.update(text), cipher.final()]);

  return {
    iv: iv.toString('hex'),
    encryptedData: encrypted.toString('hex')
  };
}

export const decrypt = (hash: IEncryption): string => {
   const encryptedData = Buffer.from(hash.encryptedData, 'hex');
   const decipher = crypto.createDecipheriv('aes-256-cbc', secretKey, Buffer.from(hash.iv, 'hex'));
   const decrypted = Buffer.concat([decipher.update(encryptedData), decipher.final()]);

   return decrypted.toString();
}