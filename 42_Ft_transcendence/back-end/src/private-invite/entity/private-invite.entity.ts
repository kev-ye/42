import { Column, Entity, PrimaryGeneratedColumn } from "typeorm";

@Entity('private_invite')
export class PrivateInviteEntity {
    @PrimaryGeneratedColumn()
    id: string;

    @Column()
    user_id: string;

    @Column()
    chat_id: string;

    @Column({nullable: true})
    emitter: string;
}