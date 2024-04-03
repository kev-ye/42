import { createTransport } from "nodemailer";
// import * as dotenv from "dotenv" // only use without docker

export function sendMail (to: string, content: string, subject?: string) {
  // dotenv.config(); // only use without docker

  const transporter = createTransport({
    host: 'smtp.outlook.com',
    port: 587,
    secure: false,
    auth: {
      user: String(process.env.MAIL_USER),
      pass: String(process.env.MAIL_PASS)
    }
  });
  const mailOptions = {
    from: String(process.env.MAIL_USER),
    to: to,
    subject: subject || 'Camagru verification',
    text: content
  }

  transporter.sendMail(mailOptions, () => {});
}