import { HttpClient } from "@angular/common/http";
import { Component, OnInit, Inject } from "@angular/core";
import { MAT_DIALOG_DATA } from "@angular/material/dialog";
import { GlobalConsts } from "src/app/common/global";

@Component({
    selector: "dialog-user",
    templateUrl: "./html/dialog-user.html"
  })
  export class DialogUser implements OnInit {
    constructor(@Inject(MAT_DIALOG_DATA) public data: any, private http: HttpClient) {
      this.username = data.username;
      this.id = data.id;
      this.my_id = data.my_id;
      
      (data.friends as any[]).forEach(val => {
        if (val.id == this.id && val.status == 2)
          this.friend = true;
      });

      (data.blocked as any[]).forEach(element => {
        if (element == this.id)
          this.blocked = true;
      });

      //this.link = `${GlobalConsts.userApi}/image/`
      
    }
  
    friend: boolean = false;
    blocked: boolean = false;
    user: any = {};
    error: boolean = false;
    ladder: any = {points: 500, win: 0, gamesPlayed: 0};
  
    ngOnInit(): void {
      this.http.get(`${GlobalConsts.userApi}/user/id/` + this.id, {withCredentials: true}).subscribe({
        next: (data: any) => {
          
          if (data)
            this.user = data;
          else
            this.error = true;
          
          this.link = `${GlobalConsts.userApi}/image/user/${this.id}?random=${Math.random()}`
          
        },
        error: (data: any) => {
          this.error = true;
          
        },
        complete: () => {
        }
      });

      this.http.get(`${GlobalConsts.userApi}/ladder/${this.id}`, {withCredentials: true}).subscribe({
        next: (data: any) => {
          this.ladder = data;
        },
        error: () => {
          alert('Could not fetch ladder details')
        }
      });
      
    }

    blockUser() {
      this.http.post(`${GlobalConsts.userApi}/block`, {
        first: this.my_id,
        second: this.id
      }, {withCredentials: true}).subscribe(() => {
        (this.data.blocked as any[]).push(this.id);
        this.blocked = true;
      });
    }

    unblockUser() {
      this.http.post(`${GlobalConsts.userApi}/unblock`, {
        first: this.my_id,
        second: this.id
      }, {withCredentials: true}).subscribe(() => {
        const index = (this.data.blocked as any[]).findIndex(val => val == this.id);
        if (index >= 0)
        {
          (this.data.blocked as any[]).splice(index);
          this.blocked = false;
        }
      });
    }

    deleteFriend() {
      this.http.patch(`${GlobalConsts.userApi}/friend`, {
        first: this.my_id,
        second: this.id
      }, {withCredentials: true}).subscribe({
        next: data => {
        this.friend = false;
      },
    error: data => {
      
    }});
    }
  
    addFriend() {
        this.http.post(`${GlobalConsts.userApi}/friend`, {first: this.my_id, second: this.id}, {withCredentials: true}).subscribe({
            next: data => {
                this.friend = true;
            }
        })
    }

  
    my_id: string = "";
    id: string = "";
    username: string = "";
    link: string = "";
  }