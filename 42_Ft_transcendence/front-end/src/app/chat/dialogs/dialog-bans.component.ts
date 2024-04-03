import { HttpClient } from "@angular/common/http";
import { Component, OnInit, Inject } from "@angular/core";
import { MAT_DIALOG_DATA, MatDialogRef, MatDialog } from "@angular/material/dialog";
import { timeout } from "rxjs";
import { Socket } from "socket.io-client";
import { GlobalConsts } from "src/app/common/global";
import { DialogMute } from "./dialog-mute.component";
import { DialogUser } from "./dialog-user.component";

@Component({
    selector: "dialog-bans",
    templateUrl: "./html/dialog-bans.html"
  })
  export class DialogBans {
    constructor(private http: HttpClient, @Inject(MAT_DIALOG_DATA) public data: any, public dialogRef: MatDialogRef<DialogBans>, public dialog: MatDialog) {
      this.fetchBans();
    }

    public bans: any[] = [];
    public users: any[] = [];
  
    fetchBans() {
      this.http.get(`${GlobalConsts.userApi}/channels/ban/` + this.data.chat.id).subscribe(val => {
        this.bans = val as any[];
      })
    }


    unbanUser(usr: any) {
      this.http.patch(`${GlobalConsts.userApi}/channels/ban`, {
        chat_id: this.data.chat.id,
        user_id: usr.user_id
      }, {withCredentials: true}).subscribe({next: res => {
        const index = this.bans.findIndex(val => val.user_id == usr.user_id);
        
        if (index >= 0)
          this.bans.splice(index);
      }});
    }
  }