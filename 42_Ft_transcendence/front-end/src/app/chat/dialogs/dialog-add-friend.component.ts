import { HttpClient } from "@angular/common/http";
import { Component, ElementRef, Inject, ViewChild } from "@angular/core";
import { MatDialogRef, MAT_DIALOG_DATA } from "@angular/material/dialog";
import { GlobalConsts } from "src/app/common/global";

@Component({
    templateUrl: './html/dialog-add-friend.html'
})
export class DialogAddFriend {
    constructor(private http: HttpClient, @Inject(MAT_DIALOG_DATA) private data: any,
    private dialog: MatDialogRef<DialogAddFriend>) {}

    public text: string = "";
    @ViewChild('error') error: ElementRef<HTMLDivElement>;

    inputEvent(username: string) {
        this.text = username;
    }

    submitFriend(username: string) {
        this.error.nativeElement.textContent = '';
        if (!username)
            return;
        this.http.get(`${GlobalConsts.userApi}/user/name/` + username, {withCredentials: true}).subscribe({
            next: data => {                
                if (!data)
                    this.error.nativeElement.textContent = 'Could not find user';
                else
                {
                    this.http.post(`${GlobalConsts.userApi}/friend`, {
                        first: this.data.my_id,
                        second: (data as any).id
                    }, {withCredentials: true}).subscribe({
                        next: data => {                        
                            this.error.nativeElement.textContent = 'Invite sent to ' + username;
                        },
                        error: data => {
                            this.error.nativeElement.textContent = 'Could not add user';
                        }
                });
                }
            }
        });

    }
}