import { Column, CreateDateColumn, Entity, PrimaryGeneratedColumn } from 'typeorm'

//table for channels' message history

@Entity('channels_history')
export class ChatHistoryEntity {
    
    @PrimaryGeneratedColumn('uuid')
    id: string; //auto-generated id

    @Column()
    user_id: string; //user (identified by his 42 id) who sent message

    @Column('text')
    chat_id: string; //chat_id where the message was sent

    @CreateDateColumn()
    created: Date; //auto-generated date

    @Column({type: "text", nullable: true})
    message: string; //message

    @Column()
    type: number;
    //1: message
    //2: invite to play pending
    //3: invite to play expired
}