import { haveAccess } from "../service/auth.js";
import { uploadImage } from "../service/file.js";
import { getAllImage, getImage, removeImage } from "../service/file.js";
import AbstractView from "./AbstractView.js";

export default class extends AbstractView {
  constructor() {
    super();

    this.setTitle('Montage');
    this.fileArray = [];
    this.filter = '';
  }

  async getHtml() {
    return await haveAccess().then(async res => {
      if (res) {
        return `
        <h1 class="common-title" >Montage</h1>

        <hr class="common-separator">

          <div class="cam-container">
            <div class="cam-content">
              <video id="cam-open" class="cam-open" autoplay playsinline></video>
              <ul class="cam-filter-container">
                <li><canvas id="cam-filter-sepia" class="cam-filter-sepia"></canvas></li>
                <li><canvas id="cam-filter-grayscale" class="cam-filter-grayscale"></canvas></li>
                <li><canvas id="cam-filter-brightness" class="cam-filter-brightness"></canvas></li>
                <li><canvas id="cam-filter-contrast" class="cam-filter-contrast"></canvas></li>
              </ul>
              <canvas id="cam-take-by-camera" class="cam-open" style="display: none;"></canvas>
              <button id="cam-button-snap" class="cam-snap-btn material-icons">photo_camera</button>
              <button id="cam-collect-publish" class="cam-publish-btn material-icons" style="display: none;">publish</button>
              <button id="cam-collect-cancel" class="cam-cancel-btn material-icons" style="display: none;">cancel</button>
            </div>
            <div>
              <ul id="cam-image-collect" class="cam-image-collect-container"></ul>
            </div>
            <div class="cam-image-upload-container">
              <input type="file" id="cam-load-image" name="cam-load-image" accept=image/jpeg>
              <button id="cam-upload-image">Upload</button>
            </div>
          </div>
        `;
      }
      else return '';
    })
  }

  async openCamera() {
    const openCamera = document.getElementById('cam-open');
    const snapBtn = document.getElementById('cam-button-snap');
    const publishBtn = document.getElementById('cam-collect-publish')
    const cancelBtn = document.getElementById('cam-collect-cancel');

    this.snapBtnSwitch(false);
    this.addFilter();
  
    await navigator.mediaDevices.getUserMedia({
      audio: false,
      video: true
    })
    .then(stream => {
      openCamera.srcObject = stream;
      openCamera.addEventListener('loadedmetadata', async () => {
        const imageInfo = {
          width: openCamera.videoWidth,
          height: openCamera.videoHeight,
          imageIdx: 0
        };

        snapBtn.onclick = () => {
          this.createNewThumbnail(openCamera, imageInfo);
          this.activeCamera(openCamera, stream, true);
        }

        publishBtn.onclick = async () => {
          await this.uploadThumbnail().then();
          await this.loadCollectImage().then();
          this.activeCamera(openCamera, stream, false);
        }

        cancelBtn.onclick = () => {
          this.activeCamera(openCamera, stream, false);
        }
      });
    })
    .catch(err => {
      alert('Your browser don\'t support camera!');
    });
  }

  async uploadImageFromFile() {
    const fileLoaded = document.getElementById('cam-load-image');
    const uploadBtn = document.getElementById('cam-upload-image');

    uploadBtn.onclick = async() => {
      const file = fileLoaded.files[0];
      if (file && file.type !== 'image/jpeg') {
        alert('You only can upload a jpeg image');
        return ;
      }

      if (!file) {
        alert('Upload a jpeg image!');
        return ;
      }

      const fileData = await this.blobToDataUrl(file);
      const res = await uploadImage(fileData).then(data => data);
      if (!res) alert('Some upload failed!');
      else {
        alert('Upload success!');
        await this.loadCollectImage().then();
        fileLoaded.value = '';
      }
    }
  }

  async blobToDataUrl(blob) {
    return new Promise(resolve => {
      const reader = new FileReader();
      reader.onload = (e) => { return resolve(e); }
      reader.readAsDataURL(blob);
    }).then(e => e.target.result);
  }

  addFilter() {
    const filterSepia = document.getElementById('cam-filter-sepia');
    const filterGrayscal = document.getElementById('cam-filter-grayscale');
    const filterBrightness = document.getElementById('cam-filter-brightness');
    const filterContrast = document.getElementById('cam-filter-contrast');

    const filterArray = [filterSepia, filterGrayscal, filterBrightness, filterContrast];
    for (const filter of filterArray) {
      filter.width = 150;
      filter.height = 150;
      this.exampleCtx(filter.getContext("2d"))
    }

    const openCameraFilter = document.getElementById('cam-open').style;

    filterSepia.onclick = () => {
      this.snapBtnSwitch(true);
      openCameraFilter.filter = this.filter = this.filterSepia();
    }

    filterGrayscal.onclick = () => {
      this.snapBtnSwitch(true);
      openCameraFilter.filter = this.filter = this.filterGrayscal();
    }

    filterBrightness.onclick = () => {
      this.snapBtnSwitch(true);
      openCameraFilter.filter = this.filter = this.filterBrightness();
    }

    filterContrast.onclick = () => {
      this.snapBtnSwitch(true);
      openCameraFilter.filter = this.filter = this.filterContrast();
    }
  }

  exampleCtx(ctx) {
    ctx.beginPath();
    ctx.arc(75, 75, 50, 0, Math.PI * 2, true);
    ctx.moveTo(110, 75);
    ctx.arc(75, 75, 35, 0, Math.PI, false);
    ctx.moveTo(65, 65);
    ctx.arc(60, 65, 5, 0, Math.PI * 2, true);
    ctx.moveTo(95, 65);
    ctx.arc(90, 65, 5, 0, Math.PI * 2, true);
    ctx.stroke();
  }

  activeCamera(camera, stream, on) {
    const canvas = document.getElementById('cam-take-by-camera');
    const snapBtn = document.getElementById('cam-button-snap');
    const publishBtn = document.getElementById('cam-collect-publish')
    const cancelBtn = document.getElementById('cam-collect-cancel');

    if (on === true) {
      camera.srcObject = null;
      camera.style.display = 'none';
      canvas.style.display = '';
      snapBtn.style.display = 'none';
      publishBtn.style.display = '';
      cancelBtn.style.display = '';
    }
    else {
      camera.style.display = '';
      camera.srcObject = stream;
      canvas.style.display = 'none';
      snapBtn.style.display = '';
      publishBtn.style.display = 'none'
      cancelBtn.style.display = 'none';
    }
  }

  async loadCollectImage() {
    const collect = document.getElementById('cam-image-collect');
    const res = await getAllImage().then(res => res);
    this.fileArray = Array.from(res.files).sort((file1, file2) => {
      if (file1.date > file2.date) return 1;
      else if (file1.date < file2.date) return -1;
      return 0;
    });

    const childNodeFromCollect = Array.from(collect.childNodes);
    for (const child of childNodeFromCollect)
      collect.removeChild(child);

    for (const file of this.fileArray)
      await this.createImage(file);
  }

  async createImage(file) {
    const collect = document.getElementById('cam-image-collect');

    const data = await getImage(file.id);
    if (data && data.user === file.user) {
      const newList = document.createElement('li');
      const newImage = document.createElement('img');
      const deleteImgBtn = document.createElement('span');

      newList.classList.add('cam-image-collect-thumbnail-container');

      newImage.id = file.id;
      newImage.src = file.data;
      newImage.classList.add('cam-image-collect-thumbnail');

      deleteImgBtn.id = data.id;
      deleteImgBtn.classList.add('cam-image-delete', 'material-icons');;
      deleteImgBtn.innerHTML = 'close';
      deleteImgBtn.onclick = async () => {
        if (confirm('You really want delete this image?') === true) {
          this.fileArray.splice(this.fileArray.indexOf(file), 1);
          await this.deleteImage(newList, file.id);
        }
      }
      
      collect.appendChild(newList);
      newList.appendChild(newImage);
      newList.appendChild(deleteImgBtn);
    }
  }

  async deleteImage(imageNode, nodeId) {
    const collect = document.getElementById('cam-image-collect');

    const res = await removeImage(nodeId).then(data => data);
    if (res) alert(`Image ${nodeId} has delete!`);
    else {
      alert('Something wrong!');
      return ;
    }
    collect.removeChild(imageNode);
  }

  createNewThumbnail(src, imageInfo) {
    const canvas = document.getElementById('cam-take-by-camera')

    canvas.width = imageInfo.width;
    canvas.height = imageInfo.height;
    canvas.getContext('2d').filter = this.filter;
    canvas.getContext('2d').drawImage(src, 0, 0);
  }

  async uploadThumbnail() {
    const thumbnail = document.getElementById('cam-take-by-camera');
    const context = thumbnail.getContext('2d');
    const image = thumbnail.toDataURL('image/jpeg', 1.0);
  
    const res = await uploadImage(image).then(data => data);
    if (!res) alert('Some upload failed!');
    else {
      alert('Upload success!');
      context.clearRect(0, 0, thumbnail.width, thumbnail.height);
    }
  }

  snapBtnSwitch(onOff) {
    const snapBtn = document.getElementById('cam-button-snap');

    snapBtn.disabled = onOff ? false : true;
    if (snapBtn.disabled === true) snapBtn.classList.add( 'cam-snap-btn-off');
    else snapBtn.classList.remove('cam-snap-btn-off');
  }

  filterSepia() { return 'sepia(100%)' };
  filterGrayscal() { return 'grayscale(100%)' };
  filterBrightness() { return 'brightness(0.35)' };
  filterContrast() { return 'contrast(140%)' };
}