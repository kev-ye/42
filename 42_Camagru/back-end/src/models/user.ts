import { ObjectId } from "mongodb";
import { IEncryption } from "../services/encrypt.service";

export interface IUser {
  username: string,
  password: string,
  email: string,
  notify: boolean,
  _oldPassword?: string,
  _activated?: boolean,
  _id?: ObjectId
}

export class User {
  constructor(
    public username: string,
    public password: IEncryption,
    public email: string,
    public notify: boolean,
    public _activated?: boolean,
    public _id?: ObjectId
  ) {}
}