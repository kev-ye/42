import { User } from "../models/user";
import { collections } from "./db.service";

// Requirements
export async function requireUniqueUserInfo(
  username: string,
  password: string,
  email: string): Promise<boolean> {
    const uname = requireUsername(username) && await uniqueUsername(username);
    const psw = requirePassword(password);
    const mail = requireEmail(email);

    if (!uname || !psw || !mail) return false;
    return true;
}

export async function uniqueUsername(userName: string): Promise<boolean> {
  const query = { username: userName };
  const user = await collections.users?.findOne(query) as unknown as User;

  return !user;
}

export function requireUsername(userName: string): boolean {
  const require = /^[a-zA-Z0-9]{6,16}$/;
  return require.test(userName);
}

export function requirePassword(password: string): boolean {
  const require = /^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])[a-zA-Z0-9]{8,16}$/;
  return require.test(password);
}

export function requireEmail(email: string) : boolean {
  const require = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/;
  return require.test(email);
}
