import { Column, Entity, PrimaryGeneratedColumn } from "typeorm";

@Entity('moderator')
export class ModeratorEntity {
    @PrimaryGeneratedColumn('uuid')
    id: string;

    @Column()
    user_id: string;

    @Column()
    chat_id: string;
}