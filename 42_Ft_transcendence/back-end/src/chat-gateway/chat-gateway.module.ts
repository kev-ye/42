import { Module } from '@nestjs/common';

import { ActiveUsersModule } from 'src/active-users/active-users.module';
import { ChannelsModule } from 'src/channels/channels.module';
import { ChatHistoryModule } from 'src/chat-history/chat-history.module';
import { PrivateModule } from 'src/private/private.module';
import { UserModule } from 'src/user/user.module';
import { ChatGateway } from './chat.gateway';

@Module({
  imports: [
    ActiveUsersModule,
    ChannelsModule,
    UserModule,
    PrivateModule,
    ChatHistoryModule,
  ],
  providers: [
    {
      provide: 'CHAT_GATEWAY',
      useClass: ChatGateway,
    },
  ],
  exports: [
    {
      provide: 'CHAT_GATEWAY',
      useClass: ChatGateway,
    },
  ],
})
export class ChatGatewayModule {}
