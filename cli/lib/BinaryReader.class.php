<?php

class ddns__BinaryReader {
	public function __construct($data) {
		$this->_offset = 0;
		$this->_data = $data;
		$this->_size = strlen($data);
	}

	private function _checkAccess($n_bytes, $label) {
		$new_offset = $this->_offset + $n_bytes;

		if ($new_offset >= $this->_size) {
			$offset = $this->_offset;
			$size = $this->_size;

			throw new Exception(
				"Refusing to read $label from buffer as it would overflow (offset={$offset},size=$size)"
			);
		}
	}

	public function readU8() {
		$this->_checkAccess(1, "u8");

		$byte = ord($this->_data[$this->_offset]);
		$this->_offset++;

		return $byte;
	}

	public function readU16BE() {
		$this->_checkAccess(2, "u16be");

		$higher_byte = ord($this->_data[$this->_offset]);
		$lower_byte = ord($this->_data[$this->_offset + 1]);
		$this->_offset += 2;

		return ($higher_byte << 8) | $lower_byte;
	}

	public function readU32BE() {
		$this->_checkAccess(4, "u32be");

		$b4 = ord($this->_data[$this->_offset]);
		$b3 = ord($this->_data[$this->_offset + 1]);
		$b2 = ord($this->_data[$this->_offset + 2]);
		$b1 = ord($this->_data[$this->_offset + 3]);
		$this->_offset += 4;

		$value  = 0;
		$value |= ($b4 << 24);
		$value |= ($b3 << 16);
		$value |= ($b2 <<  8);
		$value |= ($b1 <<  0);

		return $value;
	}

	public function readChar() {
		$this->_checkAccess(1, "char");

		$byte = $this->_data[$this->_offset];
		$this->_offset++;

		return $byte;
	}

	public function readCString() {
		$str = "";

		while (true) {
			$byte = $this->readU8();

			if ($byte === 0) break;

			$str .= chr($byte);
		}

		return $str;
	}

	public function readU8Array($n_elements) {
		$this->_checkAccess($n_elements, "u8");

		$array = [];

		for ($i = 0; $i < $n_elements; ++$i) {
			array_push($array, $this->readU8());
		}

		return $array;
	}
}

?>
