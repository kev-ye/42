import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { MainComponent } from './main/main.component';
import { UserLoginComponent } from './user-login/user-login.component';
import { UserSubscriptionComponent } from './user-subscription/user-subscription.component';
import { UserComponent } from './user/user.component';
import { ChatComponent } from './chat/chat.component';
import { DialogChannelSettings } from './chat/dialogs/dialog-channel-settings.component';
import { DialogCreateChat } from './chat/dialogs/dialog-create-chat.component';
import { DialogInvite } from './chat/dialogs/dialog-invite-channel.component';
import { DialogProtectedChat } from './chat/dialogs/dialog-protected-chat.component';
import { DialogSpectator } from './chat/dialogs/dialog-spectator.component';
import { DialogUser } from './chat/dialogs/dialog-user.component';
import { DialogAddFriend } from './chat/dialogs/dialog-add-friend.component';
import { DialogMuted } from './chat/dialogs/dialog-muted.component';
import { DialogMute } from './chat/dialogs/dialog-mute.component';
import { SharedMaterialModule } from './common/shared-material.module';
import { TwoFactorComponent } from './two-factor/two-factor.component';
import { GameComponent } from './game/game.component';
import { GameRoomComponent } from './game-room/game-room.component';
import { MatchMakingComponent } from './match-making/match-making.component';
import { GameRoomTestComponent } from './game-room-test/game-room-test.component';
import { DialogError } from './game/dialogs/error.component';
import { SpectateRoom } from './spectate-room/spectate-room.component';
import { DialogChangeUsername } from './user/dialogs/dialog-change-username.component';
import { DialogChangeImage } from './user/dialogs/dialog-change-image.component';
import { DialogModerators } from './chat/dialogs/dialog-moderators.component';
import { DialogBans } from './chat/dialogs/dialog-bans.component';

@NgModule({
  declarations: [
    AppComponent,
    MainComponent,
    UserLoginComponent,
    UserSubscriptionComponent,
    TwoFactorComponent,
    GameComponent,
    UserComponent,
    ChatComponent,
    DialogCreateChat,
    DialogInvite,
    DialogProtectedChat,
    DialogSpectator,
    DialogUser,
    DialogChannelSettings,
    DialogAddFriend,
    DialogMuted,
    DialogMute,
    DialogError,
    DialogBans,
    DialogModerators,
    DialogChangeUsername,
    DialogChangeImage,
    GameRoomComponent,
    MatchMakingComponent,
    GameRoomTestComponent,
    SpectateRoom
  ],
  imports: [
    BrowserModule,
    BrowserAnimationsModule,
    SharedMaterialModule,
    AppRoutingModule,
    FormsModule,
    ReactiveFormsModule,
    HttpClientModule,

  ],
  bootstrap: [AppComponent]
})
export class AppModule {}
