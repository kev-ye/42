import { Column, Entity, PrimaryGeneratedColumn } from "typeorm";

@Entity('channels')
export class ChannelEntity {
    @PrimaryGeneratedColumn('uuid')
    id: string;

    @Column()
    name: string;

    @Column()
    access: number;
    //0 : open
    //1 : protected
    //2 : private

    @Column({nullable: true})
    password?: string;

    @Column({nullable: true})
    creator_id: string;
}