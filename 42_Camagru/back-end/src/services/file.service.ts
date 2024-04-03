import { ObjectId } from "mongodb";
import { promises } from "fs";

import { IFile, File } from "../models/file";
import { collections } from "./db.service";

export async function createFolder(dirpath: string) {
  await promises.mkdir("upload", { recursive: true }).then();
  await promises.mkdir(`upload/${dirpath}`, { recursive: true }).then();
}

export async function uploadFile(file: string, path: string, user: string) {
  const addFile = await collections.files?.insertOne({
    path: path,
    user: user,
    _date: new Date(),
    _social: { like: [], comment: [] }
  });

  await promises.writeFile(`${path}/${addFile?.insertedId.toJSON()}`, file);
}

export async function getAllFileContent(dirPath: string, data: IFile[]) {
  try {
    const files = await promises.readdir(dirPath);

    for (const file of files) {
      try {
        const fileInfo = await collections.files?.findOne({ _id: new ObjectId(file) }) as unknown as File;
        const content = await promises.readFile(`${dirPath}/${file}`)
        const newData: IFile = {
          data: content.toString(),
          date: fileInfo?._date || new Date(),
          user: fileInfo?.user || '',
          id: fileInfo?._id?.toString() || '',
          social: fileInfo?._social || { like: [], comment: [] },
        };

        data.push(newData);
      }
      catch(e) {}
    }
  }
  catch(e) {}
}

export async function unlinkFile(path: string) {
  try {
    await promises.unlink(path);
  }
  catch(e) {}
}