import { Inject, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { UserService } from 'src/user/user.service';
import { Repository } from 'typeorm';
import { ChatHistoryEntity } from './entity/chat_history.entity';
import { chatHistory } from './interface/chatHistory.interface';


@Injectable()
export class ChatHistoryService {
    constructor(@InjectRepository(ChatHistoryEntity) private repo: Repository<ChatHistoryEntity>,
    @Inject('USER_SERVICE') private user: UserService) {}

    async showAll() {
        return await this.repo.find({ order: {
                created: 'ASC'
            }});
    }

    async showChat(chat_id: string) {
        /*let result: any[] = await this.repo.query('select * from history where chat_id=\''
        + chat_id
        + "\' order by created desc limit " + 20 + ";");
        */

        let result = await this.repo.find({where: {chat_id: chat_id}, order: {created: 'DESC'}});
		// let result: any[] = await this.repo.query(
		// 	`select * from history where chat_id='${chat_id}' order by created desc limit ${20};`);
        result.splice(20);
        result.reverse();
        return result;
    }

    async create(data: chatHistory) {
        const message = this.repo.create(data);
        return await this.repo.save(message);
    }

    async getMessageById(msg_id: string)
    {
        return await this.repo.findOne( { where: {id: msg_id}});
    }

    async showUser(user_id: string, channel_id?: string) {
        if (channel_id === undefined)
            return await this.repo.find({where: {user_id: user_id}});
        return await this.repo.find({where: {user_id: user_id, chat_id: channel_id}});
    }

    async deleteByChatID(chat_id: string) {
        return await this.repo.delete({chat_id: chat_id});
    }
}
