import express, { Router, Response, Request } from "express"
// import * as dotenv from "dotenv"; // only use without docker

import { collections } from "../services/db.service";
import { generateToken, decodeToken } from "../services/auth.service";
import { sendMail } from "../services/mail.service";
import { User } from "../models/user";
import { decrypt, encrypt } from "../services/encrypt.service";
import { ObjectId } from "mongodb";
import { authWithJwt, jwtData } from "../services/auth.service";

export const authRouter: Router = express.Router();
authRouter.use(express.json());
// dotenv.config(); // only use without docker

// JWT account auth
authRouter.post("/login", async (req: Request, res: Response) => {
  const { username, password } = req.body;
  if (!username || !password) {
    res.send({});
    return ;
  }

  try {
    const user = await collections.users?.findOne({ username: String(username) }) as unknown as User;
    if (!user || decrypt(user.password) !== String(password)) {
      res.send({});
      return ;
    }

    const token = generateToken(jwtData(user));
    res.send({ token });
  } catch (error) {
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    res.send({});
  }
});

authRouter.post("/verify", authWithJwt, async (req: Request, res: Response) => {
  const token = req.headers.authorization?.split(" ")[1];
  const decode = decodeToken(String(token));

  try {
    const user = await collections.users?.findOne({ _id: new ObjectId(decode._id) }) as unknown as User;
    user._activated
      ? res.send({ "activated": true })
      : res.send({ "activated": false })
  } catch (error) {
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    res.send({});
  }
});

// JWT account active
authRouter.post("/active", authWithJwt, async (req: Request, res: Response) => {
  const token = req.headers.authorization?.split(" ")[1];
  const decode = decodeToken(String(token));

  try {
    const user = await collections.users?.findOne({ username: String(decode.username) }) as unknown as User;
    if (!user) res.send({});
    else {
      const activeToken = generateToken(jwtData(user), 60 * 5);
    
      sendMail(user.email, `${process.env.API_URL || "http://localhost:3000"}/api/auth/active/verify?token=${activeToken}`);
      res.send({
        "token": true,
        "email": user.email
      });
    }
  } catch (error) {
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    res.send({});
  }
});

authRouter.get("/active/verify", authWithJwt, async (req: Request, res: Response) => {
  const token = String(req.query.token);
  const decode = decodeToken(token);

  try {
    const user = await collections.users?.findOne({ username: String(decode.username) }) as unknown as User;
    if (!user) {
      res.send({});
      return ;
    }
    else user._activated = true;

    await collections.users?.updateOne({ username: String(decode.username) }, { $set: user });
    res.redirect(`${process.env.FRONT_URL || "http://localhost:5050"}`);
  } catch (error) {
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    res.redirect(`${process.env.FRONT_URL || "http://localhost:5050"}`);
  }
});

// Reset password
authRouter.post("/reset/send", async (req: Request, res: Response) => {
  const username = String(req.body.username);

  try {
    const user = await collections.users?.findOne({ username: String(username) }) as unknown as User;
    if (!user) res.send({});
    else {
      const resetToken = generateToken(jwtData(user), 60 * 5);
      sendMail(user.email, `click this link: ${process.env.FRONT_URL || "http://localhost:5050"}/reset?token=${resetToken}`, 'Camagru password reset');
      res.send({ "send": true });
    }
  } catch (error) {
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    res.send({});
  }
});

authRouter.put("/reset/change", authWithJwt, async (req: Request, res: Response) => {
  const resetToken = String(req.query.token);
  const decode = decodeToken(resetToken);

  try {
    const user = await collections.users?.findOne({ username: String(decode.username) }) as unknown as User;
    if (!user) {
      res.send({});
      return ;
    }
    else {
      const password = String(req.body.password);
      if (!password) res.send({});
      else {
        user.password = encrypt(password);
        await collections.users?.updateOne({ username: String(decode.username) }, { $set: user });
        res.send({ "reset": true });
      }
    }
  } catch (error) {
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    res.send({});
  }
});

// Jwt utils
authRouter.get("/tokenVerify", authWithJwt, (req: Request, res: Response) => {
  res.send({ "token": true });
});