import numpy as np

class Buffer:
    def __init__(self, M, N, K):
        """
        Initialize the buffer with N banks, M entries per bank, and K bytes per entry.
        - N: Number of banks
        - M: Number of entries per bank
        - K: Size of each entry in bytes
        """
        self.N = N  # Number of banks
        self.M = M  # Number of entries per bank
        self.K = K  # Size of each entry in bytes

        self.buffer = np.zeros(M*N*K, dtype=np.uint8).reshape(M, N, K)

    def __str__(self):
        """
        Return a formatted string representation of the buffer.
        """
        buffer_str = ""
        for i in range(self.M):
            buffer_str += f"Entry {i}:  "
            for j in range(self.N):
                # 对齐
                buffer_str += f"  Bank {j+i*self.N:3}:{self.buffer[i, j]}\t"
            buffer_str += "\n"
        return buffer_str

    def get_addr(self, entry_idx, bank_idx):
        """
        Calculate the address of an entry within the buffer.
        The formula is (entry_idx * N + bank_idx) * K.
        - entry_idx: The index of the entry.
        - bank_idx: The index of the bank.
        """
        return (entry_idx * self.N + bank_idx) * self.K
    
    def read(self, bank_addr):
        """
        Read the content of a bank in the buffer.
        read N bank one time.
        - bank_addr: The address of the bank to read.
        """
        data = np.zeros(self.K)
        bank_addr_ = bank_addr // self.K
        for i in range(self.N):
            entry_idx = bank_addr_ // self.N
            bank_idx = bank_addr_ % self.N
            data = self.buffer[entry_idx, bank_idx]
        return data
    
    def write(self, bank_addr, data, byte_mask):
        """
        Write data to the buffer at the specified bank addresses.
        bank_addr: List of N addresses for the N banks.
        data:  K bytes of data to write to each bank.
        byte_mask: K bytes of mask to apply to each byte of the data.
        """
        bank_addr_ = np.array(bank_addr) // self.K
        for i in range(self.N):
            entry_idx = bank_addr_[i] // self.N
            bank_idx = bank_addr_[i] % self.N
            original_data = self.buffer[entry_idx, bank_idx]
            modified = (original_data & ~byte_mask[i] | data[i] & byte_mask[i])
            print("original_data", original_data , "|| data", data[i], "|| byte_mask", byte_mask[i], "|| modified", modified)

            self.buffer[entry_idx, bank_idx, :] = modified