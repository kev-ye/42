import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { MuteEntity } from './entity/mute.entity';

@Injectable()
export class MuteService {
    constructor(@InjectRepository(MuteEntity) private repo: Repository<MuteEntity>) {}

    async addMute(data: any) {
        
        const tmp = await this.repo.findOne({user_id: data.user_id, chat_id: data.chat_id});
        if (tmp) 
            return await this.repo.update({user_id: data.user_id, chat_id: data.chat_id}, data);
        const result = this.repo.create(data); 
        return await this.repo.save(result);
    }

    async deleteMute(data: any) {
        //return await this.repo.delete({first: data.first, second: data.second});
    }

    async deleteAllByChatId(chat_id: string) {
        return await this.repo.delete({chat_id: chat_id});
    }

    async getMute(chatID: string, userID: string) {
        return await this.repo.findOne({chat_id: chatID, user_id: userID});
    }
}
