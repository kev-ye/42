import { Injectable, Logger } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { PrivateInviteEntity } from './entity/private-invite.entity';

@Injectable()
export class PrivateInviteService {
    constructor(@InjectRepository(PrivateInviteEntity) private repo: Repository<PrivateInviteEntity>) {}

    async createInvite(data: any)
    {
        
        if (await this.repo.findOne({chat_id: data.chat_id, user_id: data.user_id}))
            return;
        const tmp = this.repo.create(data);
        if (tmp)
        {
            
            return await this.repo.save(tmp);
        }
    }

    async isInvited(userID: string, chatID: string) {
        return await this.repo.findOne({user_id: userID, chat_id: chatID});
    }

    async deleteAllByChat(chatID: string) {
        await this.repo.delete({chat_id: chatID});
    }
}
