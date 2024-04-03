import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { PrivateMessageEntity } from './entity/private_message.entity';

@Injectable()
export class PrivateService {
    constructor(@InjectRepository(PrivateMessageEntity) private repo: Repository<PrivateMessageEntity>) {}

    async postMessage(userID: string, data: {to: string, type: number, message?: string}) {
        const tmp = this.repo.create({from: userID, ...data});
        return await this.repo.save(tmp);
    }

    async getMessages(data: {first: string, second: string}) {
        const tmp = await this.repo.find({where : [
            {from: data.first, to: data.second},
            {from: data.second, to: data.first}
        ], order: {date: 'DESC'}});
        tmp.splice(20);
        tmp.reverse();
        let result = [];
        tmp.forEach(val => {
            result.push({user_id: val.from, message: val.message, type: val.type});
        });
        return result;
    }
}
