import express, { Express } from 'express';

import { connectToDB } from './src/services/db.service'

import { userRouter } from "./src/routes/user";
import { authRouter } from "./src/routes/auth";
import { uploadRouter } from './src/routes/file';

const port = 3000;
const app: Express = express();

connectToDB()
  .then(() => {
    app.use('/api/users', userRouter);
    app.use('/api/auth', authRouter);
    app.use('/api/file', uploadRouter);

    app.listen(port, () => {
      console.log(`Server is running on http://localhost:${port}`);
    });
  })
  .catch((error: Error) => {
    console.error("Database connection failed", error);
    process.exit();
  });
