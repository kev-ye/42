import { Column, Entity, PrimaryColumn, PrimaryGeneratedColumn } from "typeorm";

@Entity({name: 'active_users'})
export class activeUserEntity {
    @PrimaryColumn()
    id: string;

    @Column({nullable: true})
    chat_id: string;

    @Column({nullable: true})
    user_id: string;
}