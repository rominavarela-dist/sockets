package mx.iteso;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class Struct {
	
	int x;	
	float y;
	char z;
	
	public Struct() {
		
	}
	
	public void readBytes(byte[] bytes) {
		ByteBuffer buff = ByteBuffer.wrap(bytes).order(ByteOrder.LITTLE_ENDIAN);
		this.x = buff.getInt();
		this.y = buff.getFloat();
		this.z = (char) buff.get();
	}
	
	public byte[] toByteArray() {
		ByteBuffer buff = ByteBuffer.allocate(Struct.sizeInBytes()).order(ByteOrder.LITTLE_ENDIAN);
		buff.putInt(this.x);
		buff.putFloat(this.y);
		buff.put((byte)this.z);
		return buff.array();
	}
	
	public static int sizeInBytes() {
		return Integer.BYTES + Float.BYTES + Character.BYTES;
	}
	
	@Override
	public String toString() {
		return "[ \n    x: "+x+
				 ",\n    y: "+y+
				 ",\n    z: "+z+
				 "\n]";
	}
	
}
