import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { MuteService } from './mute.service';
import { MuteController } from './mute.controller';
import { MuteEntity } from './entity/mute.entity';
import { ChannelsModule } from 'src/channels/channels.module';

@Module({
  imports: [TypeOrmModule.forFeature([MuteEntity])],
  providers: [
    {
      provide: 'MUTE_SERVICE',
      useClass: MuteService
    }
  ],
  exports: [
    {
      provide: 'MUTE_SERVICE',
      useClass: MuteService
    }
  ],
  controllers: [MuteController]
})
export class MuteModule {}
