import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { BlockController } from './block.controller';
import { BlockEntity } from './entity/block.entity';
import { BlockService } from './block.service';

@Module({
  imports: [
    TypeOrmModule.forFeature([BlockEntity]),
  ],
  controllers: [BlockController],
  providers: [
    {
      provide: 'BLOCK_SERVICE',
      useClass: BlockService
    }
  ],
  exports: [
    {
      provide: 'BLOCK_SERVICE',
      useClass: BlockService
    }
  ]
})
export class BlockModule {}
