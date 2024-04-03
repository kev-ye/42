import { HttpClient } from "@angular/common/http";
import { Component, OnInit, Inject } from "@angular/core";
import { MAT_DIALOG_DATA, MatDialogRef, MatDialog } from "@angular/material/dialog";
import { timeout } from "rxjs";
import { Socket } from "socket.io-client";
import { GlobalConsts } from "src/app/common/global";
import { DialogMute } from "./dialog-mute.component";
import { DialogUser } from "./dialog-user.component";

@Component({
    selector: "dialog-moderators",
    templateUrl: "./html/dialog-moderators.html"
  })
  export class DialogModerators {
    constructor(private http: HttpClient, @Inject(MAT_DIALOG_DATA) public data: any, public dialogRef: MatDialogRef<DialogModerators>, public dialog: MatDialog) {
      this.fetchModerators(); 
           
    }
    public moderators: any[] = [];
    public users: any[] = [];
  
    fetchModerators() {
      this.http.get(`${GlobalConsts.userApi}/moderator/` + this.data.chat.id).subscribe(val => {
        this.moderators = val as any[];
      })
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
        user_id: usr.user_id
      }, {withCredentials: true}).subscribe({next: res => {
        const index = this.moderators.findIndex(val => val.user_id == usr.user_id);
        
        if (index >= 0)
          this.moderators.splice(index);
      }});
    }
  }