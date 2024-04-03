import { HttpClient } from "@angular/common/http";
import { Component, OnInit, Inject } from "@angular/core";
import { MAT_DIALOG_DATA, MatDialogRef, MatDialog } from "@angular/material/dialog";
import { timeout } from "rxjs";
import { Socket } from "socket.io-client";
import { GlobalConsts } from "src/app/common/global";
import { DialogMute } from "./dialog-mute.component";
import { DialogUser } from "./dialog-user.component";

@Component({
    selector: "dialog-spec",
    templateUrl: "./html/dialog-spectator.html"
  })
  export class DialogSpectator implements OnInit{
    constructor(private http: HttpClient, @Inject(MAT_DIALOG_DATA) public data: any, public dialogRef: MatDialogRef<DialogSpectator>, public dialog: MatDialog) {
      http.get(`${GlobalConsts.userApi}/moderator/` + data.chat.id).subscribe(val => {
        this.moderators = val as any[];
        
      })      
    }
    public moderators: any[] = [];
    public users: any[] = [];
  
    fetchUsers() {
      this.http.get(`${GlobalConsts.userApi}/active-users/` + this.data.chat.id, {withCredentials: true}).subscribe(val => {
          
          this.users = val as any[];
          let result: any[] = [];
          for (let tmp of this.users)
          {
            if (result.findIndex(data => data.id == tmp.id) == -1)
              result.push(tmp);
          }
          this.users = result;
      })
    }

    isModerator(usr: any) {
      if (this.moderators.find(val => val.user_id == usr.id))
        return true;
      return false;
    }

    modUser(usr: any) {
      
      this.http.post(`${GlobalConsts.userApi}/channels/moderator`, {
        chat_id: this.data.chat.id,
        user_id: usr.id
      }, {withCredentials: true}).subscribe({next: res => {
        this.moderators.push({chat_id: this.data.chat.id, user_id: usr.id});
      }});
    }

    unmodUser(usr: any) {
      this.http.patch(`${GlobalConsts.userApi}/channels/moderator`, {
        chat_id: this.data.chat.id,
        user_id: usr.id
      }, {withCredentials: true}).subscribe({next: res => {
        const index = this.moderators.findIndex(val => val.user_id == usr.id);
        
        if (index >= 0)
          this.moderators.splice(index);
      }});
    }
  
    ngOnInit(): void {
      this.fetchUsers();
    }

    muteUser(usr: any) {
      const tmp = this.dialog.open(DialogMute, {
        data: {
          user_id: usr.id,
          chat_id: this.data.chat.id
        }
      });
    }
  
    banUser(usr: any) {
      
    const sock: Socket = this.data.socket;
    sock.emit('ban', {
       user_id: usr.id,
       chat_id: this.data.chat.id
     });
     setTimeout(() => {
       this.fetchUsers();
     }, 1000);
     
    }
  
    openUserProfile(user: any) {
      //this.dialogRef.close();
      
      const ref = this.dialog.open(DialogUser, {
        data: {
          username: user.name,
          id: user.id,
          my_id: this.data.my_id,
          friends: this.data.friends,
          blocked: this.data.blocked
        }
      });
      
  
    }
  }