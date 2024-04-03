export default class {
  constructor() {}

  // initialize dialog
  init(setting = {}) {
    const app = document.getElementById('app');
    const dialog = document.createElement('div');

    dialog.innerHTML = setting.template || '';

    app.appendChild(dialog);

    this.modal = document.getElementById(setting.modal || '');
    this.openBtn = document.getElementById(setting.openBtn || '');
    this.cancelBtn = document.getElementById(setting.cancelBtn || '');

    this.cancelSpan = document.getElementById(setting.close || '');
  }

  // open dialog by click event
  open() {
    this.openBtn.onclick = () => {
      this.modal.style.display = "block";
    };

    this.openBtn.onclick();
  }

  // close dialog by click event
  close() {
    this.cancelSpan.onclick = () => {
      this.modal.style.display = "none";
    };

    if (this.cancelBtn) {
      this.cancelBtn.onclick  = () => {
        this.modal.style.display = "none";
      };
    }
  }

  // show dialog manually
  show() {
    this.modal.style.display = "block";
  }

  // hide dialog manually
  hide() {
    this.modal.style.display = "none";
  }

  // action about accept button (if exist)
  async accept() {}

  // action about cancel button (if exist)
  async cancel() {}
}