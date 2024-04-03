 import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { BlockEntity } from './entity/block.entity';


@Injectable()
export class BlockService {
    constructor(@InjectRepository(BlockEntity) private repo: Repository<BlockEntity>) {}

    async blockUser(data: {first: string, second: string}) {
        if (await this.repo.findOne({
            where: [
                {first: data.first, second: data.second},
            ]
        }))
        {
            return ;
        }
        const tmp = this.repo.create({first: data.first, second: data.second});
        return await this.repo.save(tmp);
    }

    async unblockUser(data: {first: number, second: number}) {
        const tmp = await this.repo.findOne({
            where: [
                {first: data.first, second: data.second},
            ]
        });

        if (!tmp)
        {
            return ;
        }
        return await this.repo.remove(tmp);
    }


    //return list of IDs of blocked users by 'id'
    async getList(id: number) {
        const tmp = await this.repo.find({
            where: [
                {first: id},
            ]
        });
        
        let result = [];
        tmp.forEach(data => {
            result.push(data.second);
        })
        return result;
    }

    async deleteBlockByUserID(userID: string) {
        await this.repo.delete({first: userID});
        return await this.repo.delete({second: userID});
    }
}
