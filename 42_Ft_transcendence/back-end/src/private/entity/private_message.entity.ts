import { Column, CreateDateColumn, Entity, PrimaryGeneratedColumn } from "typeorm";

// table for private messages

@Entity('private_messages')
export class PrivateMessageEntity {
	@PrimaryGeneratedColumn('uuid')
	id: string; //auto-generated id

	@CreateDateColumn()
	date: string; //auto-generated create date

	@Column()
	from: string; //user (identified by his 42id) who sent message

	@Column()
	to: string; //user (identified by his 42id) who received the message

	@Column({ nullable: true, type: "text" })
	message: string;

	@Column()
	type: number;
	//1 : private message
	//2 : invite to play pending
	//3 : invite to play expired
}
