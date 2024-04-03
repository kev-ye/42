import express, { Request, Response, Router } from "express";

import { User, IUser } from "../models/user";
import { authWithJwt, generateToken, decodeToken, jwtData } from "../services/auth.service";
import { collections } from "../services/db.service";
import { encrypt, decrypt } from "../services/encrypt.service";
import { requireEmail, requirePassword, requireUniqueUserInfo } from "../services/user.service";
import { sendMail } from "../services/mail.service";

export const userRouter: Router = express.Router();
userRouter.use(express.json());

// dev: get all users
// userRouter.get('/', async (req: Request, res: Response) => {
//   try {
//     const users = (await collections.users?.find({}).toArray()) as unknown as User[];

//     res.send(users);
//   } catch (error) {
//     // eslint-disable-next-line @typescript-eslint/ban-ts-comment
//     // @ts-ignore
//     res.send(error?.message);
//   }
// })

// dev: get user by name
// userRouter.get("/dev/:username", async (req: Request, res: Response) => {
//   const username = req?.params?.username;

//   try {
//     const query = { username: String(username) };
//     const user = (await collections.users?.findOne(query)) as unknown as User;

//     user
//       ? res.send({
//           ...user,
//           password: decrypt(user.password)
//         })
//       : res.send(`User with username: ${username} not found`);
//   } catch (error) {
//     res.send(`Unable to find matching document with username: ${req.params.username}`);
//   }
// });

// get user info
userRouter.get("/user", authWithJwt, async (req: Request, res: Response) => {
  const token = req.headers.authorization?.split(" ")[1];
  const decode = decodeToken(String(token));

  try {
    const user = await collections.users?.findOne({ username: String(decode.username) }) as unknown as User;
    user
      ? res.send({
          "info": true,
          "username": user.username,
          "email": user.email,
          "notify": user.notify
        })
      : res.send({});
  } catch (error) {
    res.send({});
  }
});

// insert new user
userRouter.post('/create', async (req: Request, res: Response) => {
  try {
    const newUser = req.body as IUser;

    if (!(await requireUniqueUserInfo(
      String(newUser.username),
      String(newUser.password),
      String(newUser.email),
    ))) {
      res.send({});
      return ;
    }
    const result = await collections.users?.insertOne({
      ...newUser,
      notify: true,
      password: encrypt(newUser.password),
      _activated: false,
    });

    if (result) {
      const activeToken = generateToken(jwtData(newUser), 60 * 5);

      sendMail(newUser.email, `${process.env.API_URL || "http://localhost:3000"}/api/auth/active/verify?token=${activeToken}`);
      res.send({ "created": true });
    } else res.send({});

  } catch (error) {
    console.error(error);
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    res.send({});
  }
})

// update user
userRouter.put('/update/:username', authWithJwt, async (req: Request, res: Response) => {
  const username = req?.params?.username;

  try {
    const user = req.body as IUser;
    const encryptPsw = (await collections.users?.findOne({ username: String(username) }) as unknown as User).password;
    const decryptPsw = decrypt(encryptPsw);

    if (!user.password) user.password = decryptPsw;
  
    if (user._oldPassword && user.password && user._oldPassword !== decryptPsw) {
        res.send({});
        return ;
    }

    if (String(username) === String(user.username)) {
      if (!requirePassword(String(user.password)) || !(requireEmail(String(user.email)))) {
        res.send({});
        return ;
      }
    }
    else {
      if (!(await requireUniqueUserInfo(
        String(user.username),
        String(user.password),
        String(user.email),
      ))) {
        res.send({});
        return ;
      }
    }

    const updateUser = {
      ...user,
      password: encrypt(user.password)
    };
    delete updateUser._oldPassword;

    const query = { username: String(username) };
    const ifUser = await collections.users?.findOne(query) as unknown as User;

    if (ifUser) {
      await collections.users?.updateOne(query, { $set: updateUser });
      res.send({
        "updated": true,
        "token": generateToken(jwtData({
          ...ifUser,
          ...updateUser
        }))
      });
    }
    else res.send({});
  }
  catch (error) {
    console.error(error);
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    res.send({});
  }
})
