import { Component, ElementRef, Inject, OnInit, ViewChild } from "@angular/core";
import { MatDialogRef, MAT_DIALOG_DATA } from "@angular/material/dialog";

@Component({
    templateUrl: './html/error.html',
    selector: 'dialog-error'
}) export class DialogError implements OnInit {
    constructor(@Inject(MAT_DIALOG_DATA) private data: any, private ref: MatDialogRef<DialogError>) {

    }

    public text: string = ""

    ngOnInit(): void {
        if (this.data.error)
        {
            this.text = this.data.error;
        }
        else
        {
            this.ref.close();
        }
    }


    
}