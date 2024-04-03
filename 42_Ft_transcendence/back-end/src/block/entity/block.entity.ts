import { Column, Entity, PrimaryColumn, PrimaryGeneratedColumn } from "typeorm";

//table for blocked user

@Entity('block')
export class BlockEntity {
    @PrimaryGeneratedColumn('uuid')
    id: string; //Auto-generated ID

    @Column({nullable: false})
    first: string; // user (identified by his 42 id) who blocked the second user

    @Column({nullable: false})
    second: string; // user (identified by his 42 id) who got blocked by the first user
}