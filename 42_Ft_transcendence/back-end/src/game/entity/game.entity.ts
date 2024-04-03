import { Column, CreateDateColumn, Entity, PrimaryColumn, PrimaryGeneratedColumn } from "typeorm";

@Entity('games')
export class GameEntity {
    @PrimaryGeneratedColumn('uuid')
    id: string; //this id is being used as room name to communicate with players

    @CreateDateColumn()
    created: Date;

    @Column({nullable: true})
    first: string;  //first player's socket ID

    @Column({nullable: true})
    second: string; //second player's socket ID

    @Column({nullable: true})
    first_user: string;

    @Column({nullable: true})
    second_user: string;

    @Column({default: 0})
    first_score: number;

    @Column({default: 0})
    second_score: number;
    
    @Column({default: 5})
    limit_game: number;

    @Column({default: 0})
    game_state: number;

    //0: waiting
    //1: playing
    //2: finished

    @Column({default: 0})
    power: number;
    //0 - none
    //2 - speed x2
    //4 - teleportation

    @Column({nullable: true})
    creator_id: string; //userID of game's creator
}