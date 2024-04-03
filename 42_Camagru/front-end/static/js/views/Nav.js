import AbstractView from "./AbstractView.js";
import { isLogin } from "../service/auth.js";

export default class extends AbstractView {
  constructor() {
    super();
  };

  async getHtml() {
    return await isLogin().then((res) => {
      return res
        ? `
          <nav class="nav-container">
            <div>
              <a href="/" class="nav-content-index" data-link>Camagru</a>
            </div>
            <div>
              <a href="/montage" class="nav-content-montage material-icons" data-link>photo_camera</a>
            </div>
            <div>
              <a href="/user" class="nav-content-user material-icons" data-link>person</a>
              <button id="user-exit" class="nav-content-exit material-icons"">logout</button>
            </div>
          </nav>
        `
        : `
          <nav class="nav-container">
            <div>
              <a href="/" class="nav-content-index" data-link>Gallery</a>
            </div>
            <div>
              <button id="sign-in" class="nav-content-login">Sign-in</button>
              <button id="sign-up" class="nav-content-logout">Sign-up</button>
            </div>          
          </nav>
        `
    });
  }
}