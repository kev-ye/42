import { Column, CreateDateColumn, Entity, PrimaryColumn } from 'typeorm';

// table for users
@Entity('users')
export class UserEntity {
  @PrimaryColumn({ unique: true })
  id: string; // 42 id

  @CreateDateColumn()
  created: Date; // auto-generated date

  @Column({ unique: true, type: 'text' })
  login: string; // 42 login

  @Column({ unique: true, nullable: true })
  name: string; // username

  @Column({ nullable: true })
  avatar: string; // avatar

  @Column({ nullable: true })
  fortyTwoAvatar: string; // link to 42 avatar

  @Column({ nullable: true })
  email: string; // 42 email (?)

  @Column({ nullable: true })
  online: number; // online stats

  @Column({ nullable: true })
  twoFactorSecret: string;

  @Column({ nullable: true })
  twoFactorQR: string;
}
