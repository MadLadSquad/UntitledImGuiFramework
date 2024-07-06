'use strict'

var bWebGPUEnabled = false;

async function configure_WebGPU() {
    if (navigator.gpu !== undefined && navigator.gpu !== null)
    {
        const adapter = await navigator.gpu.requestAdapter();
        if (adapter !== undefined && adapter !== null)
        {
            const device = await adapter.requestDevice();
            if (device !== undefined && device !== null)
            {
                bWebGPUEnabled = true;
                Module.preinitializedWebGPUDevice = device;
            }
        }
    }
}
configure_WebGPU();