import { Module, OnModuleInit } from '@nestjs/common';
import { ScheduleModule } from '@nestjs/schedule';
import { TypeOrmModule } from '@nestjs/typeorm';
import { LadderModule } from 'src/ladder/ladder.module';
import { PlayersModule } from 'src/players/players.module';
import { UserModule } from 'src/user/user.module';
import { GameEntity } from './entity/game.entity';
import { GameController } from './game.controller';
import { GameGateway } from './game.gateway';
import { GameService } from './game.service';

@Module({
  imports: [TypeOrmModule.forFeature([GameEntity]), PlayersModule, UserModule, LadderModule],
  controllers: [GameController],
  providers: [GameService, GameGateway],
  exports: [GameService, GameGateway]
})
export class GameModule {
}