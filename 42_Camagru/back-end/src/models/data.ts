import { ObjectId } from "mongodb";

export interface IJwtData {
  username: string,
  _id?: ObjectId,
  _activated?: boolean
}