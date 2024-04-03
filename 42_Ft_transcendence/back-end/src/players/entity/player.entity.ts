import cluster from "cluster";
import { Column, Entity, PrimaryGeneratedColumn } from "typeorm";

@Entity('players')
export class PlayerEntity {
    @PrimaryGeneratedColumn('uuid')
    id: string;

    @Column({nullable: true})
    user_id: string;

    @Column({nullable: true})
    socket_id: string;

    @Column({nullable: true})
    game_id: string;

    @Column({default: 0})
    status: number;
    //0 - no status
    //1 - looking for game (matchmaking)
    //2 - playing ?
    //3 - spectating ?
}