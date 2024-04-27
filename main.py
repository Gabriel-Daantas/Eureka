from fastapi import FastAPI, UploadFile, File, HTTPException
from fastapi.responses import JSONResponse
from scapy.all import rdpcap
from typing import List

app = FastAPI()

def process_pcap(file_path: str) -> dict:
    pcap_data = rdpcap(file_path)
    
    report = {
        "packet_count": len(pcap_data),

    }
    return report

@app.post("/analyze_pcap/")
async def analyze_pcap(file: UploadFile = File(...)):
    if file.filename.endswith(".pcap"):
        file_contents = await file.read()
        with open(file.filename, "wb") as f:
            f.write(file_contents)
        report = process_pcap(file.filename)
        return report
    else:
        raise HTTPException(status_code=400, detail="File must be in .pcap format")

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)
