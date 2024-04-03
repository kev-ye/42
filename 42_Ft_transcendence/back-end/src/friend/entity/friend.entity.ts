import { Column, Entity, PrimaryGeneratedColumn } from "typeorm";

//table for friend relationships between users

@Entity('friends')
export class FriendEntity {
    @PrimaryGeneratedColumn('uuid')
    id: string; //auto-generated id

    @Column()
    first: string; //user (identified by his 42 id) who invited first

    @Column()
    second: string; //user (identified by his 42 id) who got invited

    @Column()
    status: number;
    //1 - invite pending
    //2 - friends
    
}