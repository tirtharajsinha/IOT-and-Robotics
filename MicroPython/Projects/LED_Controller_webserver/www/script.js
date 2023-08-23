// Constants
const canvas = document.getElementById('color-canvas');
const ctx = canvas.getContext('2d');
ctx.globalCompositeOperation = "destination-out";
const colorHandle = document.getElementById('color-handle');
const brightnessSlider = document.getElementById('brightness-slider');
const brightnessHandle = document.getElementById('brightness-handle');
const brightnessInput = document.getElementById('brightness');
const rgbInput = document.getElementById('rgb');
const hexInput = document.getElementById('hex');
const colorPreview = document.getElementById('color-preview');
let can_run = true;
const colorPicker = {
   radius: 125,
   brightness: 50,
   hue: 0,
   saturation: 100,
};

// Color Conversion Functions
function hsbToRgb(h, s, b) {
   h /= 360;
   s /= 100;
   b /= 100;

   let r, g, bb;

   if (s === 0) {
      r = g = bb = b;
   } else {
      const hueToRgb = (p, q, t) => {
         if (t < 0) t += 1;
         if (t > 1) t -= 1;
         if (t < 1 / 6) return p + (q - p) * 6 * t;
         if (t < 1 / 2) return q;
         if (t < 2 / 3) return p + (q - p) * (2 / 3 - t) * 6;
         return p;
      };

      const q = b < 0.5 ? b * (1 + s) : b + s - b * s;
      const p = 2 * b - q;

      r = hueToRgb(p, q, h + 1 / 3);
      g = hueToRgb(p, q, h);
      bb = hueToRgb(p, q, h - 1 / 3);
   }

   return [Math.round(r * 255), Math.round(g * 255), Math.round(bb * 255)];
}

function rgbToHex(r, g, b) {
   return `#${r.toString(16).padStart(2, '0')}${g.toString(16).padStart(2, '0')}${b.toString(16).padStart(2, '0')}`;
}


function sendPixel(r, g, b, a) {
   fetch(`/setneopixel?r=${r}&g=${g}&b=${b}&a=${a}`)
      .then(res => res.json())
      .then(out => {
         console.log(out);
      })
      .catch(err => { throw err });
}

function updateColor() {
   if (!can_run) {
      return;
   }
   const [r, g, b] = hsbToRgb(colorPicker.hue, colorPicker.saturation, colorPicker.brightness);
   const hex = rgbToHex(r, g, b);

   rgbInput.value = `rgb(${r}, ${g}, ${b})`;
   hexInput.value = hex;
   brightnessInput.value = colorPicker.brightness;
   colorPreview.style.backgroundColor = hex;
   sendPixel(r, g, b, colorPicker.brightness);
   can_run = false;
   setTimeout(() => {
      can_run = true;
   }, 1000);

}



function generateColorGradient() {
   const gradient = ctx.createConicGradient(0, colorPicker.radius, colorPicker.radius);
   const angleStep = (2 * Math.PI) / 360;

   for (let angle = 0; angle < 2 * Math.PI; angle += angleStep) {
      const [r, g, b] = hsbToRgb((((angle * 180) / Math.PI) + 180), 100, colorPicker.brightness);
      const colorStop = angle / (2 * Math.PI);
      gradient.addColorStop(colorStop, `rgb(${r}, ${g}, ${b})`);
   }

   ctx.clearRect(0, 0, canvas.width, canvas.height);
   ctx.fillStyle = gradient;
   ctx.fillRect(0, 0, canvas.width, canvas.height);

   const gradient2 = ctx.createRadialGradient(colorPicker.radius, colorPicker.radius, 0, colorPicker.radius, colorPicker.radius, colorPicker.radius);
   let [r, g, b] = hsbToRgb(0, 0, colorPicker.brightness);
   gradient2.addColorStop(0, `rgba(${r}, ${g}, ${b}, 1)`);
   gradient2.addColorStop(0.05, `rgba(${r}, ${g}, ${b}, 1)`);
   gradient2.addColorStop(1, `rgba(${r}, ${g}, ${b}, 0)`);

   ctx.fillStyle = gradient2;
   ctx.fillRect(0, 0, canvas.width, canvas.height);
}

// Event Handlers
function handleColorCanvas(event) {
   const rect = canvas.getBoundingClientRect();
   const x = event.clientX - rect.left;
   const y = event.clientY - rect.top;

   const dx = x - colorPicker.radius;
   const dy = y - colorPicker.radius;
   const distance = Math.sqrt(dx * dx + dy * dy);

   if (distance <= colorPicker.radius) {
      const angle = Math.atan2(dy, dx);
      colorPicker.hue = (angle * 180) / Math.PI + 180;
      colorPicker.saturation = (distance / colorPicker.radius) * 100;
      updateColor();

      const handleX = colorPicker.radius + Math.cos(angle) * distance;
      const handleY = colorPicker.radius + Math.sin(angle) * distance;
      colorHandle.style.left = `${handleX}px`;
      colorHandle.style.top = `${handleY}px`;
   }
}

function handleBrightnessSlider(event) {
   const rect = brightnessSlider.getBoundingClientRect();
   const y = event.clientY - rect.top;

   if (y >= 0 && y <= rect.height - 8) {
      colorPicker.brightness = (1 - y / (rect.height - 8)) * 100;
      updateColor();

      const handleY = (1 - colorPicker.brightness / 100) * (rect.height - 8);
      brightnessHandle.style.top = `${handleY}px`;

      generateColorGradient();
   }
}

// Initialize Color Picker
canvas.width = colorPicker.radius * 2;
canvas.height = colorPicker.radius * 2;

generateColorGradient();

colorHandle.style.left = `0`;
colorHandle.style.top = `${colorPicker.radius}px`;

const rect = brightnessSlider.getBoundingClientRect();
brightnessHandle.style.top = `${rect.height * (colorPicker.brightness / 100)}px`;

updateColor();

// Event Listeners
canvas.addEventListener('mousedown', (event) => {
   handleColorCanvas(event);

   const handleMouseMove = (event) => {
      handleColorCanvas(event);
   };

   const handleMouseUp = () => {
      document.removeEventListener('mousemove', handleMouseMove);
      document.removeEventListener('mouseup', handleMouseUp);
   };

   document.addEventListener('mousemove', handleMouseMove);
   document.addEventListener('mouseup', handleMouseUp);
});

brightnessSlider.addEventListener('mousedown', (event) => {
   handleBrightnessSlider(event);

   const handleMouseMove = (event) => {
      handleBrightnessSlider(event);
   };

   const handleMouseUp = () => {
      document.removeEventListener('mousemove', handleMouseMove);
      document.removeEventListener('mouseup', handleMouseUp);
   };

   document.addEventListener('mousemove', handleMouseMove);
   document.addEventListener('mouseup', handleMouseUp);
});