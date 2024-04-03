import { Component, Inject } from "@angular/core";
import { MAT_DIALOG_DATA } from "@angular/material/dialog";

@Component({
    templateUrl: './html/dialog-muted.html'
})
export class DialogMuted {
    constructor(@Inject(MAT_DIALOG_DATA) private data: any) {  
              
        this.date = new Date(data.date);

        const tmp = new Date();
        this.diff = this.date.getTime() - tmp.getTime();
        this.diff /= 1000;
        if (this.diff < 0)
            this.diff = 0;
        this.str = this.diff.toFixed(0).toString();
        
    }

    date: Date = new Date();
    str: string = "";
    diff: number;

    getRemaining() {
        const tmp = new Date();
        this.date.getTime()
        //let diff = this.date.getTime() - tmp.getTime();
        let diff = tmp.getTime();

        if (diff < 0)
            diff = 0;
        return diff;
    }
}